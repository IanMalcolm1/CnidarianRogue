#include "Adventure/PlayerManager.h"
#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/PathfindingRoute.h"
#include "Algorithms/PathingSpecs.h"
#include "Entities/Abilities/AbilityFactory.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Actors/ActorUtils.h"
#include "Entities/Components.h"
#include "Entities/Items/ItemFactory.h"
#include "Enums/PlayerCommands.h"
#include "Enums/TurnTime.h"
#include "EventListener/Listener.h"
#include "Topography/LocalMap.h"
#include "Topography/TerrainMap.h"
#include "Topography/TileCoordinates.h"

PlayerManager::PlayerManager(GameLog* gameLog) :
   actorMan(nullptr), player(nullptr), map(nullptr),
   inputState(PLAYER_INPUT_MOVE), autoActing(false), 
   gameLog(gameLog) {

      playerArena = malloc(sizeof(ActorEntity) + 64);
      player = new(playerArena) ActorEntity(0, sizeof(ActorEntity), sizeof(ActorEntity)+64, true);

      player->stats.maxHealth = 10000;
      player->stats.health = player->stats.maxHealth;

      player->description.name = "Arta";
      player->description.desc = "It's you.";

      player->display.symbol = ASYM_AT;
      player->display.symbolColor = Color(207,181,59);

      player->faction = FACTION_GOOD;

      player->stats.speed = FULL_TURN_TIME;

      player->ability = AbilityFactory::makeHealAbility(7);
   }

PlayerManager::~PlayerManager() {
   player->~ActorEntity();
   free(playerArena);
}

bool PlayerManager::processDirectionalCommand(PlayerCommand direction) {
   TileCoords currCoords;
   if (inputState == PLAYER_INPUT_MOVE) {
      currCoords = player->location;
   }
   else {
      currCoords = map->getFocusTileLocation();
   }

   TileCoords newCoords = getNewLocation(currCoords, direction);

   if (!map->isInMapBounds(newCoords)) {
      return false;
   }

   if (inputState == PLAYER_INPUT_MOVE) {
      if (map->thereIsAnActorAt(newCoords) && player->isHostileTo(map->getActorAt(newCoords))) {
         actorUtils->doMeleeAttack(player, map->getActorAt(newCoords));
         actorMan->addActorToTurnQueue(player, player->stats.speed);
         return true;
      }

      else if (map->isTraversibleAt(newCoords) && !map->thereIsAnActorAt(newCoords)) {
         map->setPlayerLocation(player, newCoords);
         actorMan->addActorToTurnQueue(player, player->stats.speed);
         return true;
      }
      return false;
   }
   else if (inputState == PLAYER_INPUT_LOOK) {
      map->setLookTile(newCoords);
      return false;
   }
   else if (inputState == PLAYER_INPUT_SELECT) {
      map->setLookTile(newCoords);
      return false;
   }
   else {
      return false;
   }
}



TileCoords PlayerManager::getNewLocation(TileCoords curr, PlayerCommand direction) {
   if (direction < 3) {
      curr.y--;
   }
   else if (direction < 6) {
      curr.y++;
   }
   if (direction % 3 == 1) {
      curr.x++;
   }
   else if (direction % 3 == 2) {
      curr.x--;
   }

   return curr;
}


bool PlayerManager::processMouseClick(bool isRightClick) {
   if (isRightClick) {
      map->lookAtMouseTile();
      return false;
   }

   else if (inputState == PLAYER_INPUT_SELECT) {
      processConfirm();
      return true;
   }

   else {
      startAutoMove();
      return false;
   }
}


ActorEntity* PlayerManager::getPlayer() {
   return player;
}

void PlayerManager::placePlayer(TileCoords location) {
   map->setPlayerLocation(player, location);
}

void PlayerManager::updateInputState(PlayerCommand command) {
   if (command == PC_TOGGLE_LOOK) {
      if (inputState == PLAYER_INPUT_LOOK) {
         resetInputState();
      }
      else {
         map->setLookTile(player->location);
         inputState = PLAYER_INPUT_LOOK;
      }
   }

   else if (command == PC_TOGGLE_SELECT) {
      if (inputState == PLAYER_INPUT_SELECT) {
         resetInputState();
      }
      else {
         inputState = PLAYER_INPUT_SELECT;
         PathingSpecs pathSpecs = PathingSpecs(PATH_LINE, TRAV_INCLUDE_UNSEEN_TILES);
         pathSpecs.lineInfo.range = ((RangedComp*) player->inventory.getMagicWeapon()->getComponent(COMPONENT_RANGED))->range;
         map->setHighlightRouteSpecs(pathSpecs);
      }
   }

   else {
      resetInputState();
   }
}

void PlayerManager::resetInputState() {
   map->stopLooking();
   map->setHighlightRouteSpecs(PathingSpecs(PATH_ROUTE, TRAV_INCLUDE_UNSEEN_TILES));
   inputState = PLAYER_INPUT_MOVE;
}

void PlayerManager::lookAtMouseTile() {
   inputState = PLAYER_INPUT_LOOK;
   map->lookAtMouseTile();
}

bool PlayerManager::doAutoAct() {
   bool stillMoving = doAutoMovement();

   if (stillMoving && player->canSeeHostile()) {
      clearAutoAct();
      gameLog->sendMessage("Auto move cancelled due to visible enemy.");
   }

   return stillMoving;
}

void PlayerManager::clearAutoAct() {
   autoMoveRoute.clear();
   autoActing = false;
}

void PlayerManager::startAutoMove() {
   if (inputState == PLAYER_INPUT_LOOK) {
      map->stopLooking();
      inputState = PLAYER_INPUT_MOVE;
   }

   autoMoveRoute = map->getHighlightedPath();
   autoActing = true;
}

bool PlayerManager::doAutoMovement() {
   if (!autoMoveRoute.hasNextTile()) {
      clearAutoAct();
      autoActing = false;
      return false;
   }

   TileCoords newTile = autoMoveRoute.getNextTile();

   if (map->isTraversibleAt(newTile)) {
      map->setPlayerLocation(player, newTile);
      autoMoveRoute.incrementProgress();
      actorMan->addActorToTurnQueue(player, player->stats.speed);
      return true;
   }
   else {
      clearAutoAct();
      autoActing = false;
      return false;
   }
}

bool PlayerManager::isAutoActing() { return autoActing; }



bool PlayerManager::pickUpItem() {
   auto itemsInTile = map->getItemsAt(player->location);
   if (itemsInTile->empty()) {
      return false;
   }

   actorUtils->doItemPickup(itemsInTile->at(0), player);

   actorMan->addActorToTurnQueue(player, player->stats.speed);

   return true;
}

void PlayerManager::waitTurn() {
   actorMan->addActorToTurnQueue(player, player->stats.speed);
}

bool PlayerManager::doAbility() {
   bool didTurn = abilityMan->doAbility(player->ability, player);
   if (didTurn) {
      actorMan->addActorToTurnQueue(player, player->stats.speed);
   }
   return didTurn;
}

bool PlayerManager::attemptLevelChange() {
   TerrainType terrainType = map->getTerrainTypeAt(player->location);
   if (terrainType == TERRAIN_DOWNSTAIRS) {
      return true;
   }
   return false;
}

bool PlayerManager::processConfirm() {
   if (inputState == PLAYER_INPUT_SELECT) {
      PathingRoute line = map->getHighlightedPath();
      actorUtils->attackAlongRoute(player, player->inventory.getMagicWeapon(), line);
      actorMan->addActorToTurnQueue(player, player->stats.speed);
      return true;
   }

   return false;
}


void PlayerManager::setSceneDependencies(ActorManager* actorMan, LocalMap* localMap, EffectManager* effectManager, ItemManager* itemManager, ItemFactory* itemFactory, ActorUtils* actorUtils, AbilityManager* abilityMan) {
   this->actorMan = actorMan;
   map = localMap;
   effectMan = effectManager;
   itemMan = itemManager;
   this->itemFactory = itemFactory;
   this->actorUtils = actorUtils;
   this->abilityMan = abilityMan;
}

void PlayerManager::armPlayer() {
   player->inventory.setMeleeWeapon(itemFactory->makeBasicDagger({-1,-1}));
   player->inventory.setNatMagicWeapon(itemFactory->getNaturalWeapon(NATWEAP_FORCE_CANTRIP));
}


void PlayerManager::processEvent(EventType event) {
   if (event == EVENT_PLAYERDED) {
      clearAutoAct();
   }
   else if (event == EVENT_PLAYERDAMAGED && autoActing) {
      gameLog->sendMessage("Auto move cancelled due to damage taken.");
      clearAutoAct();
   }
}

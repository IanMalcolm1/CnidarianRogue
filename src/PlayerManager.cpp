#include "Adventure/PlayerManager.h"
#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Actors/ActorUtils.h"
#include "Entities/Components.h"
#include "Entities/Items/ItemFactory.h"
#include "Enums/TurnTime.h"
#include "EventListener/Listener.h"
#include "Topography/TerrainMap.h"

PlayerManager::PlayerManager(GameLog* gameLog) :
turnQueue(nullptr), player(nullptr), map(nullptr),
inputState(PLAYER_INPUT_MOVE), autoActing(false), 
gameLog(gameLog) {
   
   playerArena = malloc(sizeof(ActorEntity) + 64);
   player = new(playerArena) ActorEntity(0, sizeof(ActorEntity), sizeof(ActorEntity)+64, true);

   player->stats.maxHealth = 150;
   player->stats.health = player->stats.maxHealth;

   player->description.name = "Tamren";
   player->description.desc = "It's you.";

   player->display.symbol = ASYM_AT;
   player->display.symbolColor = MyColor(255,215,0);

   player->faction = FACTION_GOOD;

   player->stats.speed = FULL_TURN_TIME;
}

PlayerManager::~PlayerManager() {
   player->~ActorEntity();
   free(playerArena);
}

bool PlayerManager::processDirectionalCommand(PlayerCommand direction) {
   TileCoords newCoords;

   if (inputState == PLAYER_INPUT_MOVE) {
      newCoords = player->location;
   }
   else {
      newCoords = map->getFocusTileLocation();
   }

   if (direction < 3) {
      newCoords.y--;
   }
   else if (direction < 6) {
      newCoords.y++;
   }
   if (direction % 3 == 1) {
      newCoords.x++;
   }
   else if (direction % 3 == 2) {
      newCoords.x--;
   }

   if (!map->isInMapBounds(newCoords)) {
      return false;
   }

   if (inputState == PLAYER_INPUT_MOVE) {
      if (map->thereIsAnActorAt(newCoords) && player->isHostileTo(map->getActorAt(newCoords))) {
         actorUtils->doAttack(player, map->getActorAt(newCoords));
         turnQueue->insertActor(player, player->stats.speed);
         return true;
      }

      else if (map->isTraversibleAt(newCoords) && !map->thereIsAnActorAt(newCoords)) {
         map->setPlayerLocation(player, newCoords);
         turnQueue->insertActor(player, player->stats.speed);
         return true;
      }
      return false;
   }
   else if (inputState == PLAYER_INPUT_LOOK) {
      map->setLookTile(newCoords);
      return false;
   }
   else {
      return false;
   }
}


void PlayerManager::processMouseClick(bool isRightClick) {
  if (inputState == PLAYER_INPUT_SELECT) {
     map->lookAtMouseTile();
     //TODO: draw selection line
  }
  else if (isRightClick) {
     map->lookAtMouseTile();
  }
  else {
     startAutoMove();
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
         map->stopLooking();
         inputState = PLAYER_INPUT_MOVE;
      }
      else {
         map->setLookTile(player->location);
         inputState = PLAYER_INPUT_LOOK;
      }
   }

   else if (command == PC_ESCAPEKEY) {
      map->stopLooking();
      inputState = PLAYER_INPUT_MOVE;
   }
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

   autoMoveRoute = map->getRouteToMouseTile();
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
      turnQueue->insertActor(player, player->stats.speed);
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

   turnQueue->insertActor(player, player->stats.speed);

   return true;
}

void PlayerManager::waitTurn() {
   turnQueue->insertActor(player, player->stats.speed);
}

bool PlayerManager::attemptLevelChange() {
   TerrainType terrainType = map->getTerrainTypeAt(player->location);
   if (terrainType == TERRAIN_DOWNSTAIRS) {
      return true;
   }
   return false;
}


void PlayerManager::setSceneDependencies(TurnQueue* queue, LocalMap* localMap, EffectManager* effectManager, ItemManager* itemManager, ItemFactory* itemFactory, ActorUtils* actorUtils) {
   turnQueue = queue;
   map = localMap;
   effectMan = effectManager;
   itemMan = itemManager;
   this->itemFactory = itemFactory;
   this->actorUtils = actorUtils;

   player->setNaturalWeapon(itemFactory->getNaturalWeapon(NATWEAP_FIST));
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

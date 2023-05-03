#include "Adventure/PlayerManager.h"
#include "Algorithms/PathfindingRoute.h"
#include "Entities/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Enums/TurnTime.h"

PlayerManager::PlayerManager() :
turnQueue(nullptr), player(nullptr), map(nullptr),
inputState(PLAYER_INPUT_MOVE), autoActing(false), 
confirmer(nullptr) {
   
   playerArena = malloc(sizeof(ActorEntity) + 64);
   player = new(playerArena) ActorEntity(0, sizeof(ActorEntity), sizeof(ActorEntity)+64);

   player->isPlayer = true;

   player->stats.maxHealth = 15;
   player->stats.health = player->stats.maxHealth;

   player->description.name = "</gold:The Player/>";
   player->description.desc = "It's you.";

   player->display.symbol = ASYM_AT;
   player->display.symbolColor = MyColor(255,215,0);

   player->faction = FACTION_GOOD;

   player->stats.baseMoveSpeed = FULL_TURN_TIME + FULL_TURN_TIME/2;
   player->stats.baseAttackSpeed = FULL_TURN_TIME + FULL_TURN_TIME/2;
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
      if (map->isTraversibleAt(newCoords) && !map->thereIsAnActorAt(newCoords)) {
         map->setPlayerLocation(player, newCoords);
         turnQueue->insert(player, player->stats.baseMoveSpeed);
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
   if (!autoMoveRoute.hasNextTile()) {
      autoActing = false;
      autoMoveRoute.clear();
      turnQueue->insert(player, 0);
      return false;
   }

   TileCoords newTile = autoMoveRoute.getNextTile();

   if (map->isTraversibleAt(newTile)) {
      map->setPlayerLocation(player, newTile);
      autoMoveRoute.incrementProgress();
      turnQueue->insert(player, player->stats.baseMoveSpeed);
   }
   else {
      autoActing = false;
      autoMoveRoute.clear();
      turnQueue->insert(player, 0);
   }

   return autoActing;
}

void PlayerManager::clearAutoAct() {
   autoMoveRoute.clear();
   autoActing = false;
}

void PlayerManager::startAutoMove() {
   autoMoveRoute = map->getRouteToMouseTile();
   autoMoveRoute.resetProgress();
   autoActing = true;
}


void PlayerManager::waitTurn() {
      turnQueue->insert(player, player->stats.baseMoveSpeed);
}


void PlayerManager::setSceneDependencies(TurnQueue* queue, LocalMap* localMap) {
   turnQueue = queue;
   map = localMap;

   turnQueue->insert(player, 0);
}

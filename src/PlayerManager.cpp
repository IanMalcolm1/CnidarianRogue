#include "PlayerManager/PlayerManager.h"
#include "Entities/ActorEntity.h"
#include "Scene/TurnQueue.h"

void PlayerManager::initialize(ActorEntity* player) {
   this->player = player;
   TileDisplay playerDisp = { ASYM_AT, {255,255,255}, {0,0,0} };
   this->player->display = playerDisp;

   turnQueue->insert(this->player, 0);
}

bool PlayerManager::processDirectionalCommand(PlayerCommand direction) {
   TileCoords oldCoords, newCoords;

   if (inputState == PLAYER_INPUT_MOVE) {
      oldCoords = newCoords = player->location;
   }
   else {
      oldCoords = newCoords = map->getFocusTileLocation();
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
         return true;
      }
      return false;
   }
   else if (inputState == PLAYER_INPUT_MOVE) {
      map->setLookTile(oldCoords, newCoords);
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

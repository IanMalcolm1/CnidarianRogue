#include "Entities/Abilities/AbilityManager.h"
#include "Enums/TurnTime.h"


void AbilityManager::initialize(GameLog* gameLog, EffectManager* effectManager, TurnQueue* turnQueue, LocalMap* map, ActorFactory* actorFactory) {
   effectMan = effectManager;
   this->turnQueue = turnQueue;
   this->gameLog = gameLog;
   this->map = map;
   this->actorFactory = actorFactory;
}

bool AbilityManager::doAbility(Ability& ability, ActorEntity* actor) {
   if (ability.type==ABILITY_NONE) {
      return false;
   }

   if (ability.currentCooldown > 0) {
      if (actor->isPlayer()) {
         std::string message = "Ability is on cooldown for ";
         message.append(std::to_string(ability.currentCooldown/FULL_TURN_TIME));
         message.append(" turns.");
         gameLog->sendMessage(message);
      }
      return false;
   }

   bool success = true;

   if (ability.type == ABILITY_HEAL) {
      effectMan->attachEffect(ability.effect, actor);
   }
   else if (ability.type == ABILITY_SPAWN_CNIDAS) {
      success = doSpawnCnidas(actor);
   }
   else {
      success = false;
   }

   if (success) {
      ability.currentCooldown = ability.cooldown;
   }
   
   return success;
}


bool AbilityManager::doSpawnCnidas(ActorEntity* actor) {
   bool success = false;
   auto surroundingTiles = map->getSurroundingTiles(actor->location);

   for (TileCoords tile : surroundingTiles) {
      if (map->isTraversibleAt(tile)) {
         actorFactory->makeCnidas(tile);
         success = true;
         break;
      }
   }

   return true;
}

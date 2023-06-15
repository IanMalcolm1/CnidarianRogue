#include "Entities/Abilities/AbilityManager.h"
#include "Entities/Abilities/Ability.h"
#include "Enums/TurnTime.h"


void AbilityManager::initialize(GameLog* gameLog, EffectManager* effectManager, TurnQueue* turnQueue) {
   effectMan = effectManager;
   this->turnQueue = turnQueue;
   this->gameLog = gameLog;
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

   if (ability.type == ABILITY_HEAL) {
      effectMan->attachEffect(ability.effect, actor);
      ability.currentCooldown = ability.cooldown;
      return true;
   }

   return false;
}

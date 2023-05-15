#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effect.h"



void EffectManager::applyEffect(Effect effect, ActorEntity* effectee) {
   switch (effect.type) {
      case EFFECT_STAT_MOD:
         applyStatModification(effect, effectee);
         break;
      default:
        break; 
   }

   switch (effect.classification) {
      case EFFECT_TIMED:
         updateTimedEffect(effect, effectee);
         break;
      case EFFECT_DOT:
         updateDoTEffect(effect, effectee);
         break;
      default:
         break;
   }
}



void EffectManager::applyStatModification(Effect effect, ActorEntity* effectee) {
   switch (effect.statModInfo.stat) {
      case STAT_HEALTH:
         effectee->stats.health += effect.statModInfo.modification;
         break;
      case STAT_MAX_HEALTH:
         effectee->stats.maxHealth += effect.statModInfo.modification;
         break;
      case STAT_STRENGTH:
         effectee->stats.strength += effect.statModInfo.modification;
         break;
      case STAT_INTELLIGENCE:
         effectee->stats.intelligence += effect.statModInfo.modification;
         break;
      case STAT_MOVE_SPEED:
         effectee->stats.baseMoveSpeed += effect.statModInfo.modification;
         break;
      case STAT_ATTACK_SPEED:
         effectee->stats.baseAttackSpeed += effect.statModInfo.modification;
         break;
      default:
         break;
   }
}


void EffectManager::removeEffect(Effect effect, ActorEntity* effectee) {
   switch (effect.type) {
      case EFFECT_STAT_MOD:
         removeStatModification(effect, effectee);
         break;
      default:
        break; 
   }
}

void EffectManager::removeStatModification(Effect effect, ActorEntity* effectee) {
   switch (effect.statModInfo.stat) {
      case STAT_HEALTH:
         effectee->stats.health -= effect.statModInfo.modification;
         break;
      case STAT_MAX_HEALTH:
         effectee->stats.maxHealth -= effect.statModInfo.modification;
         break;
      case STAT_STRENGTH:
         effectee->stats.strength -= effect.statModInfo.modification;
         break;
      case STAT_INTELLIGENCE:
         effectee->stats.intelligence -= effect.statModInfo.modification;
         break;
      case STAT_MOVE_SPEED:
         effectee->stats.baseMoveSpeed -= effect.statModInfo.modification;
         break;
      case STAT_ATTACK_SPEED:
         effectee->stats.baseAttackSpeed -= effect.statModInfo.modification;
         break;
      default:
         break;
   }
}

void EffectManager::updateDoTEffect(Effect effect, ActorEntity* effectee) {
   effect.dotInfo.duration -= effect.dotInfo.tickTime;
   if (effect.dotInfo.duration > effect.dotInfo.tickTime) {
      turnQueue->insertEffect(effect, effectee, effect.dotInfo.tickTime);
   }
}

void EffectManager::updateTimedEffect(Effect effect, ActorEntity* effectee) {
   if (effect.timedInfo.applied) {
      return;
   }
   turnQueue->insertEffect(effect, effectee, effect.timedInfo.duration);
}

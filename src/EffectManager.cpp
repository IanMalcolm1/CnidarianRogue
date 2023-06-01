#include "Adventure/Scene/EffectManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effects/Effect.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Entities/EntityDescriber.h"
#include "Logs/DebugLogger.h"


EffectDescriber* EffectManager::getEffectDescriber() {
   return &describer;
}

void EffectManager::attachEffect(Effect& effect, ActorEntity* effectee) {
   if (effect.timing != EFFECT_TIMING_DOT) {
      applyEffect(effect, effectee);
   }

   switch (effect.timing) {
      case EFFECT_TIMING_TIMED:
         attachTimedEffect(effect, effectee);
         break;
      case EFFECT_TIMING_DOT:
         attachDoTEffect(effect, effectee);
         break;
      default:
         break;
   }

   std::string msg = EntityDescriber::makeName(effectee);
   msg.append(describer.getMessage(effect));
   actorMan->sendMsgIfActorIsVisible(effectee, msg);
}

void EffectManager::applyEffect(Effect& effect, ActorEntity* effectee) {
   switch (effect.type) {
      case EFFECT_TYPE_STAT_MOD:
         applyStatModification(effect, effectee);
         break;
      case EFFECT_TYPE_DAMAGE:
         applyDamageEffect(effect, effectee);
         break;
      default:
         DebugLogger::log("Effect has no type.");
        return; 
   }
}


void EffectManager::attachDoTEffect(Effect& effect, ActorEntity* effectee) {
   Effect* activeEffect = effectee->activeEffects.getEffect(effect);

   //if this effect is new, add it to queue
   if (activeEffect == nullptr) {
      effectee->activeEffects.addEffect(effect);
      turnQueue->insertEffect(effect, effectee, effect.dotInfo.tickTime);
      return;
   }

   //if an existing effect exists, replace it
   activeEffect->dotInfo.duration = effect.dotInfo.duration;
   turnQueue->removeEffect(effect, effectee);
   turnQueue->insertEffect(effect, effectee, effect.dotInfo.tickTime);
}

void EffectManager::attachTimedEffect(Effect& effect, ActorEntity* effectee) {
   Effect* activeEffect = effectee->activeEffects.getEffect(effect);
   if (activeEffect == nullptr) {
      effectee->activeEffects.addEffect(effect);
      turnQueue->insertEffect(effect, effectee, effect.timedInfo.duration);
      return;
   }

   activeEffect->timedInfo.duration = effect.timedInfo.duration;
   turnQueue->removeEffect(effect, effectee);
   turnQueue->insertEffect(effect, effectee, effect.timedInfo.duration);
}

void EffectManager::updateEffect(Effect& effect, ActorEntity* effectee) {
   applyEffect(effect, effectee);

   switch (effect.timing) {
      case EFFECT_TIMING_TIMED:
         endTimedEffect(effect, effectee);
         break;
      case EFFECT_TIMING_DOT:
         updateDoTEffect(effect, effectee);
         break;
      default:
         break;
   }
}



void EffectManager::applyDamageEffect(Effect& effect, ActorEntity* effectee) {
   auto damageAndMsg = actorMan->calcDamage(effectee, effect.damageInfo.damage);

   std::string msg = EntityDescriber::makeName(effectee) + " takes " + damageAndMsg.second;
   actorMan->sendMsgIfActorIsVisible(effectee, msg);

   actorMan->damageActor(effectee, damageAndMsg.first);
}


void EffectManager::applyStatModification(Effect& effect, ActorEntity* effectee) {
   switch (effect.statModInfo.stat) {
      case STAT_MAX_HEALTH:
         effectee->stats.maxHealth += effect.statModInfo.modification;
         break;
      case STAT_STRENGTH:
         effectee->stats.strength += effect.statModInfo.modification;
         break;
      case STAT_INTELLIGENCE:
         effectee->stats.intelligence += effect.statModInfo.modification;
         break;
      case STAT_SPEED:
         effectee->stats.speed += effect.statModInfo.modification;
         break;
      default:
         break;
   }
}


void EffectManager::removeEffect(Effect& effect, ActorEntity* effectee) {
   if (effect.timing == EFFECT_TIMING_DOT || effect.timing == EFFECT_TIMING_TIMED) {
      turnQueue->removeEffect(effect, effectee);
   }

   switch (effect.type) {
      case EFFECT_TYPE_STAT_MOD:
         removeStatModification(effect, effectee);
         break;
      default:
        break; 
   }
}


void EffectManager::removeStatModification(Effect& effect, ActorEntity* effectee) {
   switch (effect.statModInfo.stat) {
      case STAT_MAX_HEALTH:
         effectee->stats.maxHealth -= effect.statModInfo.modification;
         break;
      case STAT_STRENGTH:
         effectee->stats.strength -= effect.statModInfo.modification;
         break;
      case STAT_INTELLIGENCE:
         effectee->stats.intelligence -= effect.statModInfo.modification;
         break;
      case STAT_SPEED:
         effectee->stats.speed -= effect.statModInfo.modification;
         break;
      default:
         break;
   }
}

void EffectManager::updateDoTEffect(Effect& effect, ActorEntity* effectee) {
   effect.dotInfo.duration -= effect.dotInfo.tickTime;

   effectee->activeEffects.getEffect(effect)->dotInfo.duration = effect.dotInfo.duration;

   if (effect.dotInfo.duration > effect.dotInfo.tickTime) {
      turnQueue->insertEffect(effect, effectee, effect.dotInfo.tickTime);
   }
   else {
      effectee->activeEffects.removeEffect(effect);
   }
}

void EffectManager::endTimedEffect(Effect& effect, ActorEntity* effectee) {
   effectee->activeEffects.removeEffect(effect);
}

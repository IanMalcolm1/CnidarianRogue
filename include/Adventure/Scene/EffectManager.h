#pragma once

#include "Adventure/Scene/TurnQueue.h"
#include "Adventure/Scene/ActorManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Effects/EffectDescriber.h"
#include "Logs/GameLog.h"


class ActorManager;

class EffectManager {
private:
   EffectDescriber describer;
   ActorManager* actorMan;
   TurnQueue* turnQueue;

   void applyDamageEffect(Effect effect, ActorEntity* effectee);

   void applyEffect(Effect effect, ActorEntity* effectee);
   void applyStatModification(Effect effect, ActorEntity* effectee);
   void removeStatModification(Effect effect, ActorEntity* effectee);
   void removeEffectFromActorList(Effect effect, ActorEntity* effectee);

   void updateDoTEffect(Effect effect, ActorEntity* effectee);
   void endTimedEffect(Effect effect, ActorEntity* effectee);

   void attachDoTEffect(Effect effect, ActorEntity* effectee);
   void attachTimedEffect(Effect effect, ActorEntity* effectee);
   void addEffectToActorList(Effect effect, ActorEntity* effectee);

public:
   EffectManager(ActorManager* actorManager, TurnQueue* turnQueue) :
   actorMan(actorManager), turnQueue(turnQueue) {};

   EffectDescriber* getEffectDescriber();

   void attachEffect(Effect effect, ActorEntity* effectee);
   void updateEffect(Effect effect, ActorEntity* effectee);
   void removeEffect(Effect effect, ActorEntity* effectee);
};

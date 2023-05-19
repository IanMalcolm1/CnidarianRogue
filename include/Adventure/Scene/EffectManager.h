#pragma once

#include "Adventure/Scene/TurnQueue.h"
#include "Adventure/Scene/ActorManager.h"
#include "Entities/Actors/ActorEntity.h"
#include "Logs/GameLog.h"


class ActorManager;

class EffectManager {
private:
   ActorManager* actorMan;
   TurnQueue* turnQueue;

   void applyDamageEffect(Effect effect, ActorEntity* effectee);

   void applyStatModification(Effect effect, ActorEntity* effectee);
   void removeStatModification(Effect effect, ActorEntity* effectee);

   void updateDoTEffect(Effect effect, ActorEntity* effectee);
   void updateTimedEffect(Effect effect, ActorEntity* effectee);

public:
   EffectManager(ActorManager* actorManager, TurnQueue* turnQueue) :
   actorMan(actorManager), turnQueue(turnQueue) {};

   void applyEffect(Effect effect, ActorEntity* effectee);
   void removeEffect(Effect effect, ActorEntity* effectee);
};

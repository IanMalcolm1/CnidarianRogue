#pragma once

#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Actors/ActorEntity.h"


class EffectManager {
private:
   TurnQueue* turnQueue;

   void applyStatModification(Effect effect, ActorEntity* effectee);
   void removeStatModification(Effect effect, ActorEntity* effectee);

   void updateDoTEffect(Effect effect, ActorEntity* effectee);
   void updateTimedEffect(Effect effect, ActorEntity* effectee);

public:
   EffectManager(TurnQueue* turnQueue) : turnQueue(turnQueue) {};

   void applyEffect(Effect effect, ActorEntity* effectee);
   void removeEffect(Effect effect, ActorEntity* effectee);
};

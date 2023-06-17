#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Entities/Abilities/Ability.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/ActorFactory.h"


class AbilityManager {
private:
   EffectManager* effectMan;
   TurnQueue* turnQueue;
   GameLog* gameLog;
   LocalMap* map;
   ActorFactory* actorFactory;

   bool doSpawnCnidas(ActorEntity* actor);

public:
   void initialize(GameLog* gameLog, EffectManager* effectManager, TurnQueue* turnQueue, LocalMap* map, ActorFactory* actorFactory);

   //Returns true if successfully used ability
   bool doAbility(Ability& ability, ActorEntity* actor);
};

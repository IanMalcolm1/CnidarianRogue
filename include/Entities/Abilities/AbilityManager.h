#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Entities/Abilities/Ability.h"


class AbilityManager {
private:
   EffectManager* effectMan;
   TurnQueue* turnQueue;
   GameLog* gameLog;

public:
   void initialize(GameLog* gameLog, EffectManager* effectManager, TurnQueue* turnQueue);

   //Returns true if successfully used ability
   bool doAbility(Ability& ability, ActorEntity* actor);
};

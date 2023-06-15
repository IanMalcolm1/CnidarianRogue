#pragma once

#include "Entities/Effects/Effect.h"
#include "Enums/TurnTime.h"


enum AbilityType {
   ABILITY_HEAL,
   ABILITY_NONE,
};

struct Ability {
   AbilityType type;
   int cooldown;
   int currentCooldown;

   union {
      Effect effect;
   };

   Ability(AbilityType type = ABILITY_NONE, int cooldown = FULL_TURN_TIME*10) :
   type(type), cooldown(cooldown), currentCooldown(0) {};
};

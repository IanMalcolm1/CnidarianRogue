#pragma once

#include "Entities/Abilities/Ability.h"


class AbilityFactory {
private:


public:
   static Ability makeHealAbility(int health = 10);
};

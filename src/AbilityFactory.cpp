#include "Entities/Abilities/AbilityFactory.h"
#include "Entities/Abilities/Ability.h"
#include "Entities/Effects/EffectFactory.h"
#include "Enums/TurnTime.h"


Ability AbilityFactory::makeHealAbility(int health) {
   Ability heal = Ability(ABILITY_HEAL);

   heal.effect = EffectFactory::makeHeal(health);

   return heal;
}

Ability AbilityFactory::makeSpawnCnidas() {
   Ability heal = Ability(ABILITY_SPAWN_CNIDAS, 7*FULL_TURN_TIME);

   return heal;
}

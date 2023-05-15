#include "Entities/EffectFactory.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effect.h"
#include "Enums/TurnTime.h"


Effect EffectFactory::makePoison(int strength) {
   Effect poison = Effect(EFFECT_DOT, EFFECT_STAT_MOD);

   poison.statModInfo.stat = STAT_HEALTH;
   poison.statModInfo.modification = -strength;

   poison.dotInfo.tickTime = FULL_TURN_TIME;
   poison.dotInfo.duration = FULL_TURN_TIME *5;

   return poison;
}


Effect EffectFactory::makeStatPowerUp(StatType stat, int strength) {
   Effect powerUp = Effect(EFFECT_PERMANENT, EFFECT_STAT_MOD);

   powerUp.statModInfo.stat = stat;
   powerUp.statModInfo.modification = strength;

   return powerUp;
}

#include "Entities/Effects/EffectFactory.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Damage.h"
#include "Entities/Effects/Effect.h"
#include "Enums/TurnTime.h"


Effect EffectFactory::makePoison(int strength) {
   Effect poison = Effect(EFFECT_POISON, EFFECT_TIMING_DOT, EFFECT_TYPE_DAMAGE);

   poison.damageInfo.damage = Damage(DAMAGE_POISON, 0, 0, 1);

   poison.dotInfo.tickTime = FULL_TURN_TIME;
   poison.dotInfo.duration = FULL_TURN_TIME*10;

   return poison;
}


Effect EffectFactory::makeStrengthen(int strength) {
   Effect powerUp = Effect(EFFECT_STRENGTH, EFFECT_TIMING_PERMANENT, EFFECT_TYPE_STAT_MOD);

   powerUp.statModInfo.stat = STAT_STRENGTH;
   powerUp.statModInfo.modification = strength;

   return powerUp;
}

Effect EffectFactory::makeEnlighten(int strength) {
   Effect powerUp = Effect(EFFECT_INTELLIGENCE, EFFECT_TIMING_PERMANENT, EFFECT_TYPE_STAT_MOD);

   powerUp.statModInfo.stat = STAT_INTELLIGENCE;
   powerUp.statModInfo.modification = strength;

   return powerUp;
}

Effect EffectFactory::makeHeal(int health) {
   Effect heal = Effect(EFFECT_HEAL, EFFECT_TIMING_INSTANT, EFFECT_TYPE_HEAL);

   heal.healInfo.health = health;

   return heal;
}

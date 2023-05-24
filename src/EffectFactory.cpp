#include "Entities/Effects/EffectFactory.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Damage.h"
#include "Entities/Effects/Effect.h"
#include "Enums/TurnTime.h"


Effect EffectFactory::makePoison(int strength) {
   Effect poison = Effect(EFFECT_CLASS_DOT, EFFECT_TYPE_DAMAGE);
   poison.description = EFFECT_DESC_POISON;

   poison.damageInfo.damage = Damage(DAMAGE_POISON, 0, 1);

   poison.dotInfo.tickTime = FULL_TURN_TIME;
   poison.dotInfo.duration = FULL_TURN_TIME*10;

   poison.maxStacks = 3;

   return poison;
}


Effect EffectFactory::makeStrengthen(int strength) {
   Effect powerUp = Effect(EFFECT_CLASS_PERMANENT, EFFECT_TYPE_STAT_MOD);

   powerUp.statModInfo.stat = STAT_STRENGTH;
   powerUp.statModInfo.modification = strength;

   powerUp.maxStacks = 9999;

   return powerUp;
}

Effect EffectFactory::makeEnlighten(int strength) {
   Effect powerUp = Effect(EFFECT_CLASS_PERMANENT, EFFECT_TYPE_STAT_MOD);

   powerUp.statModInfo.stat = STAT_INTELLIGENCE;
   powerUp.statModInfo.modification = strength;

   powerUp.maxStacks = 9999;

   return powerUp;
}

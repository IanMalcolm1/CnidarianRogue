#pragma once

#include "Entities/Damage.h"
#include "Enums/TurnTime.h"
#include "Entities/Actors/ActorStatBlock.h"


/* Timed: Last for a certain duration, then get removed.
 * DoT: Apply regularly every given tickTime time units
 *    until duration ends
 * Item-Bound: Apply until an item is removed.
 * Permanent: Apply permanently. Should be added to Entity's
 *    description or to a an array of effects that each Entity
 *    holds.
 */
enum EffectClassification {
   EFFECT_PERMANENT,
   EFFECT_TIMED,
   EFFECT_DOT,
   EFFECT_EQUIPPED,
   EFFECT_ON_DEFENSE,
   EFFECT_ON_ATTACK
};

struct TimedEffectInfo {
   bool applied;
   int duration;
};
struct DoTEffectInfo {
   int duration, tickTime;
};
struct EquippedEffectInfo {
   bool isEquipped;
};



enum EffectType {
   EFFECT_NONE,
   EFFECT_STAT_MOD,
   EFFECT_DAMAGE,
};

struct StatModEffectInfo {
   StatType stat;
   int modification;
};

struct DamageEffectInfo {
   Damage damage;
};


struct Effect {
   EffectType type;
   EffectClassification classification;

   union {
      StatModEffectInfo statModInfo;
      DamageEffectInfo damageInfo;
   };

   union {
      TimedEffectInfo timedInfo;
      DoTEffectInfo dotInfo;
      EquippedEffectInfo equippedInfo;
   };

   Effect(EffectClassification classification = EFFECT_PERMANENT, EffectType type = EFFECT_NONE)
      : type(type), classification(classification) {};


	bool operator == (const Effect effect) const {
      if (type != effect.type || classification != effect.classification) {
         return false;
      }

      if (type == EFFECT_STAT_MOD) {
         return (statModInfo.stat == effect.statModInfo.stat && statModInfo.modification == effect.statModInfo.modification);
      }
      
      return true;
	}
};

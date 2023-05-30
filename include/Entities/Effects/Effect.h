#pragma once

#include "Entities/Damage.h"
#include "Enums/TurnTime.h"
#include "Entities/Actors/ActorStatBlock.h"
#include <cwchar>


/* Timed: Last for a certain duration, then get removed.
 * DoT: Apply regularly every given tickTime time units
 *    until duration ends
 * Item-Bound: Apply until an item is removed.
 * Permanent: Apply permanently. Should be added to Entity's
 *    description or to a an array of effects that each Entity
 *    holds.
 */
enum EffectTiming {
   EFFECT_TIMING_PERMANENT,
   EFFECT_TIMING_TIMED,
   EFFECT_TIMING_DOT,
   EFFECT_TIMING_EQUIPPED,
};

struct TimedEffectInfo {
   int duration;
};
struct DoTEffectInfo {
   int duration, tickTime;
};
struct EquippedEffectInfo {
   bool isEquipped;
};



enum EffectType {
   EFFECT_TYPE_NONE,
   EFFECT_TYPE_STAT_MOD,
   EFFECT_TYPE_DAMAGE,
};

struct StatModEffectInfo {
   StatType stat;
   int modification;
   std::string getDescription();
};

struct DamageEffectInfo {
   Damage damage;
};



enum EffectDescription {
   EFFECT_DESC_POISON,
   EFFECT_DESC_STRENGTH,
   EFFECT_DESC_INTELLIGENCE,
   EFFECT_DESC_NONE, //also acts as number of effect description types
};



struct Effect {
   EffectTiming timing;
   EffectType type;
   EffectDescription description;

   int maxStacks;

   union {
      StatModEffectInfo statModInfo;
      DamageEffectInfo damageInfo;
   };

   union {
      TimedEffectInfo timedInfo;
      DoTEffectInfo dotInfo;
      EquippedEffectInfo equippedInfo;
   };

   Effect(EffectTiming timing = EFFECT_TIMING_PERMANENT, EffectType type = EFFECT_TYPE_NONE)
      : type(type), timing(timing), description(EFFECT_DESC_NONE) {};


	bool operator == (const Effect effect) const {
      if (type != effect.type || timing != effect.timing) {
         return false;
      }

      if (type == EFFECT_TYPE_STAT_MOD) {
         return (statModInfo.stat == effect.statModInfo.stat && statModInfo.modification == effect.statModInfo.modification);
      }
      if (type == EFFECT_TYPE_DAMAGE) {
         return (damageInfo.damage == effect.damageInfo.damage);
      }
      
      return true;
	}
};

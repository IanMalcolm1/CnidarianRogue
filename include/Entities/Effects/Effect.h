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
   EFFECT_TIMING_INSTANT,
};

struct TimedEffectInfo {
   int duration;

   std::string getDescription();
};
struct DoTEffectInfo {
   int duration, tickTime;

   std::string getDescription();
};
struct EquippedEffectInfo {
   bool isEquipped;

   std::string getDescription();
};



enum EffectType {
   EFFECT_TYPE_NONE,
   EFFECT_TYPE_STAT_MOD,
   EFFECT_TYPE_DAMAGE,
   EFFECT_TYPE_HEAL,
};

struct StatModEffectInfo {
   StatType stat;
   int modification;
   std::string getDescription();
};

struct DamageEffectInfo {
   Damage damage;
};

struct HealEffectInfo {
   int health;
   std::string getDescription();
};


enum EffectName {
   EFFECT_POISON,
   EFFECT_STRENGTH,
   EFFECT_INTELLIGENCE,
   EFFECT_HEAL,
   EFFECT_NONAME, //also acts as number of effect description types
};



struct Effect {
   EffectName name;
   EffectTiming timing;
   EffectType type;

   union {
      StatModEffectInfo statModInfo;
      DamageEffectInfo damageInfo;
      HealEffectInfo healInfo;
   };

   union {
      TimedEffectInfo timedInfo;
      DoTEffectInfo dotInfo;
      EquippedEffectInfo equippedInfo;
   };

   Effect(EffectName name = EFFECT_NONAME, EffectTiming timing = EFFECT_TIMING_PERMANENT, EffectType type = EFFECT_TYPE_NONE)
      : type(type), timing(timing), name(name) {};


	bool operator == (const Effect effect) const {
      return name == effect.name;
	}
};

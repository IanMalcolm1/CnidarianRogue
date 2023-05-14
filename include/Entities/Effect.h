#pragma once

#include "Enums/TurnTime.h"


enum EffectType {
   EFFECT_NONE,
   EFFECT_POISON,
   EFFECT_REGENERATION,
   EFFECT_STR_INCREASE,
   EFFECT_INT_INCREASE
};


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
   EFFECT_EQUIPPED
};

struct Effect {
   EffectType type;
   EffectClassification classification;

   int intensity;

   int duration; //For Timed and DoT effects
   int tickTime; //For DoT effects (they also use duration)

   Effect(EffectClassification classification = EFFECT_PERMANENT, EffectType type = EFFECT_NONE, int intensity = 0, int duration = 0, int tickTime = 0)
      : type(type), intensity(intensity), classification(classification), duration(duration), tickTime(tickTime) {};
};

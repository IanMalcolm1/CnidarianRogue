#pragma once

#include <vector>

enum EffectTiming {
   EFFECT_TIMING_TIMED
};

struct TimedEffectInfo {
   int duration;
};

struct Effect {
   char id;
   EffectTiming timing;
   TimedEffectInfo timedInfo;

   Effect(char id = '*') : id(id) {};

   bool operator == (const Effect effect) {
      return (id==effect.id);
   }
};

class EffectList {
private:
   std::vector<Effect> effects;

public:
   void updateEffectDurations(int turnTime);
   Effect* getEffect(Effect& effect);
   void addEffect(Effect& effect);
   void removeEffect(Effect& effect);
   void replaceEffect(Effect& replacement);
   std::vector<Effect>* getAllEffects();
};

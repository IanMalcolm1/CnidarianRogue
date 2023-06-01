#include "EffectList.h"

void EffectList::updateEffectDurations(int turnTime) {
   //only timed effects matter. DoT durations get updated on their own
   for (auto effect : effects) {
      if (effect.timing == EFFECT_TIMING_TIMED) {
         effect.timedInfo.duration -= turnTime;
      }
   }
}

Effect* EffectList::getEffect(Effect& effect) {
   for (int i=0; i<effects.size(); i++) {
      if (effects[i] == effect) {
         return &effects[i];
      }
   }
   return nullptr;
}

void EffectList::addEffect(Effect& effect) {
   effects.push_back(effect);
}

void EffectList::removeEffect(Effect& effect) {
   for (int i=0; i<effects.size(); i++) {
      if (effects[i] == effect) {
         effects.erase(effects.begin()+i);
      }
   }
}

void EffectList::replaceEffect(Effect& replacement) {
   for (int i=0; i<effects.size(); i++) {
      if (effects[i] == replacement) {
         effects[i] = replacement;
         return;
      }
   }

   effects.push_back(replacement);
}

std::vector<Effect>* EffectList::getAllEffects() {
   return &effects;
}

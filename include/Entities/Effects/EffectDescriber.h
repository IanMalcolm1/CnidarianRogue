#pragma once

#include "Entities/Effects/Effect.h"


class EffectDescriber {
private:
   std::string names[EFFECT_DESC_NONE];
   std::string adjectives[EFFECT_DESC_NONE];
   std::string messages[EFFECT_DESC_NONE];

public:
   EffectDescriber();

   std::string getAdjective(Effect& effect);
   std::string getMessage(Effect& effect);
   std::string describe(Effect& effect);
};

#pragma once

#include "Entities/Effects/Effect.h"


class EffectDescriber {
private:
   std::string names[EFFECT_NONAME];
   std::string adjectives[EFFECT_NONAME];
   std::string messages[EFFECT_NONAME];

public:
   EffectDescriber();

   std::string getAdjective(Effect& effect);
   std::string getMessage(Effect& effect);
   std::string nameAndDescribe(Effect& effect);
   std::string describe(Effect& effect);
};

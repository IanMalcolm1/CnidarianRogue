#pragma once

#include "Entities/Effects/Effect.h"


class EffectDescriber {
private:
   std::string names[EFFECT_DESC_NONE];
   std::string messages[EFFECT_DESC_NONE];

public:
   EffectDescriber();

   std::string getName(EffectDescription descID);
   std::string getMessage(EffectDescription descID);
};

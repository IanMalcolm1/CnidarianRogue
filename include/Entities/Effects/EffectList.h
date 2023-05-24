#pragma once

#include "Entities/Effects/Effect.h"
#include <vector>


class EffectList {
private:
   //Effects and their stacks
   std::vector<std::pair<Effect, int>> list;

public:
   std::pair<Effect,int>* getEffect(Effect effect);
   void addEffect(Effect effect);
   void removeEffect(Effect effect);
   std::vector<std::pair<Effect,int>>* getEffects();
};

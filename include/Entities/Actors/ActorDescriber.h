#pragma once

#include "Entities/Actors/ActorEntity.h"
#include "Entities/Effects/EffectDescriber.h"


class ActorDescriber {
   EffectDescriber* effectDescriber;

public:
   ActorDescriber() : effectDescriber(nullptr) {};

   void initialize(EffectDescriber* effectDescriber);

   std::string describe(ActorEntity* actor);
   std::string listEffects(ActorEntity* actor);
};

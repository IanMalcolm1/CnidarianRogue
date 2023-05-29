#pragma once

#include "Entities/Actors/ActorEntity.h"
#include "Entities/Effects/EffectDescriber.h"
#include "GraphicsThings/GameText.h"


class ActorDescriber {
   EffectDescriber* effectDescriber;

public:
   ActorDescriber(EffectDescriber* effectDescriber) :
   effectDescriber(effectDescriber) {};

   std::string describe(ActorEntity* actor);
};

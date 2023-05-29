#pragma once

#include "Entities/Actors/ActorEntity.h"
#include "Entities/Effects/EffectDescriber.h"
#include "GraphicsThings/GameText.h"


class ActorDescriber {
   GameTextMaker* textMaker;
   EffectDescriber* effectDescriber;

public:
   ActorDescriber(GameTextMaker* gameTextMaker, EffectDescriber* effectDescriber) : textMaker(gameTextMaker), effectDescriber(effectDescriber) {};

   void setGameTextMaker(GameTextMaker* gameTextMaker);

   GameText name(ActorEntity* actor);
   GameText describe(ActorEntity* actor);
};

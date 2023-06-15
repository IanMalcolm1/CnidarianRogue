#pragma once

#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effects/Effect.h"


class EffectFactory {
private:
   

public:
   static Effect makePoison(int strength);
   static Effect makeStrengthen(int strength);
   static Effect makeEnlighten(int strength);
   static Effect makeHeal(int health);
};

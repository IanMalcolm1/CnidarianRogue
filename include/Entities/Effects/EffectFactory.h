#pragma once

#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effects/Effect.h"


class EffectFactory {
private:
   

public:
   Effect makePoison(int strength);
   Effect makeStrengthen(int strength);
   Effect makeEnlighten(int strength);
};

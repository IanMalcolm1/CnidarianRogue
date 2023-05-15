#pragma once

#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effect.h"


class EffectFactory {
private:
   

public:
   Effect makePoison(int strength);
   Effect makeStatPowerUp(StatType stat, int strength);
};

#pragma once

#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Effects/Effect.h"
#include "Enums/TurnTime.h"


class EffectFactory {
private:
   

public:
   static Effect makePoison(int strength);
   static Effect makeStrengthen(int strength);
   static Effect makeEnlighten(int strength);
   static Effect makeHeal(int health);
   static Effect makeRegeneration(int health, int duration = FULL_TURN_TIME*10, int tickTime = FULL_TURN_TIME);
};

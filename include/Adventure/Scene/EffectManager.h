#pragma once

#include "Entities/Actors/ActorEntity.h"
#include "Entities/Components.h"


class EffectManager {
private:

public:
   void applyEffect(Effect effect, ActorEntity* effectee);

};

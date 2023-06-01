#pragma once

#include "EffectList.h"
#include <string>


struct ActorEntity {
   int id;
   EffectList activeEffects;

   ActorEntity(int id) : id(id) {};
};



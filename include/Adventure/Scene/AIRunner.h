#pragma once

#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/Randomizer.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/ActorUtils.h"
#include "Topography/LocalMap.h"


class AIRunner {
private:
   LocalMap* map;
   ActorManager* actorMan;
   ActorUtils* actorUtils;

   Randomizer randomizer;

   int wander(ActorEntity* actor);
   int approachAndWhack(ActorEntity* actor);

public:
   AIRunner(LocalMap* map, ActorManager* actorMan, ActorUtils* actorUtils) :
   map(map), actorMan(actorMan), actorUtils(actorUtils), randomizer() {};

   void runActorTurn(ActorEntity* actor);
};

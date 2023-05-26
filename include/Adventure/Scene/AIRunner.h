#pragma once

#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/Dice.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Actors/ActorUtils.h"
#include "Topography/LocalMap.h"


class AIRunner {
private:
   LocalMap* map;
   ActorManager* actorMan;
   ActorUtils* actorUtils;

   Dice dice;

   int wander(ActorEntity* actor);
   int approachAndWhack(ActorEntity* actor);

public:
   AIRunner(LocalMap* map, ActorManager* actorMan, ActorUtils* actorUtils) :
   map(map), actorMan(actorMan), actorUtils(actorUtils), dice() {};

   void runActorTurn(ActorEntity* actor);
};

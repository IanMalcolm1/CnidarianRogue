#pragma once

#include "Adventure/Scene/ActorManager.h"
#include "Algorithms/PathfindingRoute.h"
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
   PathingRoute testingRoute;

   int doWander(ActorEntity* actor);
   int doApproachAndWhack(ActorEntity* actor);
   int doShootAndApproach(ActorEntity* actor);

   int doApproachTarget(ActorEntity* actor);

   int meleeAI(ActorEntity* actor);
   int rangedAI(ActorEntity* actor);

   bool targetIsInShootRange(ActorEntity* actor);

public:
   AIRunner() : map(nullptr), actorMan(nullptr), actorUtils(nullptr) {};

   void initialize(LocalMap* map, ActorManager* actorMan, ActorUtils* actorUtils);

   void runActorTurn(ActorEntity* actor);
};

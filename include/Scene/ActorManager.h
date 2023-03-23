#pragma once

/* Intent: Have a public method you call on an actor that gets the 
 * actor's state, and runs the corresponding logic function.
 * Logic functions will be private functions of this class */

#include "GameObjects/Actor.h"
#include "Scene/TurnQueue.h"
#include "Topography/LocalMap.h"
#include "Scene/ActorPool.h"

class ActorManager {
   private:
      ActorPool actorPool;
      TurnQueue* turnQueue;
      LocalMap* map;

      int wander(Actor* actor);


      int runAction(Actor* actor);

   public:
      ActorManager(LocalMap* map, TurnQueue* turnQueue) : actorPool(ActorPool()), turnQueue(turnQueue), map(map) {};

      void runActorTurns();

      void createActorAt(TileCoords location);
      void destroyActor(Actor* actor);
      void moveActor(Actor* actor, TileCoords newLocation);
};

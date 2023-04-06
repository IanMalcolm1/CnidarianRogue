#pragma once

/* Intent: Have a public method you call on an actor that gets the 
 * actor's state, and runs the corresponding logic function.
 * Logic functions will be private functions of this class */

#include "Entities/ActorEntity.h"
#include "Entities/ActorFactory.h"
#include "Entities/EntityColiseum.h"
#include "Scene/TurnQueue.h"
#include "Topography/LocalMap.h"

class ActorManager {
   private:
      EntityColiseum<ActorEntity> actorColiseum;
      TurnQueue turnQueue;
      LocalMap* map;

      int runAction(ActorEntity* actor);

      int wander(ActorEntity* actor);

   public:
      ActorManager(LocalMap* map) :
         actorColiseum(EntityColiseum<ActorEntity>()),
         turnQueue(TurnQueue()), map(map) {};

      void runActorTurns();

      void destroyActor(ActorEntity* actor);
      void moveActor(ActorEntity* actor, TileCoords newLocation);

      ActorEntity* getActor(int id) {
         return actorColiseum.getEntity(id);
      };

      ActorFactory makeFactory();
      TurnQueue* getTurnQueue();
};

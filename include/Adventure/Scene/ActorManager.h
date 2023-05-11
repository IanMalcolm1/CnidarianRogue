#pragma once

/* Intent: Have a public method you call on an actor that gets the 
 * actor's state, and runs the corresponding logic function.
 * Logic functions will be private functions of this class */

#include "Entities/Actors/ActorFactory.h"
#include "Entities/EntityColiseum.h"
#include "Adventure/Scene/TurnQueue.h"
#include "EventListener/Blabber.h"
#include "Topography/LocalMap.h"
#include "Logs/GameLog.h"

class ActorManager : public Blabber {
   private:
      EntityColiseum<ActorEntity> actorColiseum;
      TurnQueue turnQueue;
      LocalMap* map;

      GameLog* gameLog;

      int runAction(ActorEntity* actor);

      int wander(ActorEntity* actor);
      int approachAndWhack(ActorEntity* actor);

   public:
      ActorManager(LocalMap* map, GameLog* gameLog) :
         map(map), gameLog(gameLog), turnQueue(),
         actorColiseum(EntityColiseum<ActorEntity>()) {};

      void runActorTurns();

      void destroyActor(ActorEntity* actor);
      void moveActor(ActorEntity* actor, TileCoords newLocation);
      void doAttack(ActorEntity* attacker, ActorEntity* defender);

      ActorEntity* getActor(int id) {
         return actorColiseum.getEntity(id);
      };

      ActorFactory makeFactory();
      TurnQueue* getTurnQueue();
};

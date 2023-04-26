#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/ActorEntity.h"
#include "Scene/TurnQueue.h"
#include "Topography/LocalMap.h"


class ActorFactory {
private:
   EntityColiseum<ActorEntity>* actorColiseum;
   LocalMap* map;
   TurnQueue* turnQueue;

   void registerActor(ActorEntity* actor);

public:
   ActorFactory(EntityColiseum<ActorEntity>* actorColiseum,
         TurnQueue* turnQueue, LocalMap* map) :
      map(map), turnQueue(turnQueue),
      actorColiseum(actorColiseum) {};


   ActorEntity* makeEvilSmileyFace(TileCoords location);
};

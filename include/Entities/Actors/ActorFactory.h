#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "GraphicsThings/ColorMap.h"
#include "Topography/LocalMap.h"


class ActorFactory {
private:
   EntityColiseum<ActorEntity>* actorColiseum;
   LocalMap* map;
   TurnQueue* turnQueue;

   ColorMap colorMap;

   void registerActor(ActorEntity* actor);

public:
   ActorFactory(EntityColiseum<ActorEntity>* actorColiseum,
         TurnQueue* turnQueue, LocalMap* map) :
      map(map), turnQueue(turnQueue), colorMap(),
      actorColiseum(actorColiseum) {};


   ActorEntity* makeEvilSmileyFace(TileCoords location);
};

#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Items/ItemEntity.h"
#include "Entities/Items/ItemFactory.h"
#include "GraphicsThings/ColorMap.h"
#include "Topography/LocalMap.h"


class ActorFactory {
private:
   EntityColiseum<ActorEntity>* actorColiseum;
   LocalMap* map;
   TurnQueue* turnQueue;

   ItemFactory* itemFactory;

   ColorMap colorMap;

   void registerActor(ActorEntity* actor);

public:
   ActorFactory(EntityColiseum<ActorEntity>* actorColiseum,
   TurnQueue* turnQueue, LocalMap* map, ItemFactory* itemFactory) :
   map(map), turnQueue(turnQueue), colorMap(), itemFactory(itemFactory),
   actorColiseum(actorColiseum) {};


   ActorEntity* makeEvilSmileyFace(TileCoords location);
};

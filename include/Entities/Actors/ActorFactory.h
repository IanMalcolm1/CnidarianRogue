#pragma once

#include "Algorithms/Randomizer.h"
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
   Randomizer randomizer;

   void registerActor(ActorEntity* actor);

public:
   ActorFactory() : actorColiseum(nullptr), map(nullptr), turnQueue(nullptr),
   itemFactory(nullptr) {};

   void initialize(EntityColiseum<ActorEntity>* actorColiseum, TurnQueue* turnQueue, LocalMap* map, ItemFactory* itemFactory);

   ActorEntity* makeEvilSmileyFace(TileCoords location);
   ActorEntity* makeWandCultist(TileCoords location);
};

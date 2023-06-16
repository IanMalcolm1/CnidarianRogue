#pragma once

#include "Adventure/Scene/EffectManager.h"
#include "Algorithms/Randomizer.h"
#include "Entities/EntityColiseum.h"
#include "Entities/Actors/ActorEntity.h"
#include "Adventure/Scene/TurnQueue.h"
#include "Entities/Items/ItemEntity.h"
#include "Entities/Items/ItemFactory.h"
#include "GraphicsThings/ColorLibrary.h"
#include "Topography/LocalMap.h"


class ActorFactory {
private:
   EntityColiseum<ActorEntity>* actorColiseum;
   LocalMap* map;
   TurnQueue* turnQueue;

   ItemFactory* itemFactory;
   EffectManager* effectMan;

   ColorLibrary colorMap;
   Randomizer randomizer;

   void registerActor(ActorEntity* actor);

public:
   ActorFactory() : actorColiseum(nullptr), map(nullptr), turnQueue(nullptr),
   itemFactory(nullptr) {};

   void initialize(EntityColiseum<ActorEntity>* actorColiseum, TurnQueue* turnQueue, LocalMap* map, ItemFactory* itemFactory, EffectManager* effectMan);

   ActorEntity* makeCultistWarrior(TileCoords location);
   ActorEntity* makeWandCultist(TileCoords location);
   ActorEntity* makeArmoredCultist(TileCoords location);
   ActorEntity* makeBadDog(TileCoords location);

   ActorEntity* makeCnidas(TileCoords location);
   ActorEntity* makeCultistIdol(TileCoords location);
};

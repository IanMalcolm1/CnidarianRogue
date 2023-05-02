#pragma once

#include "Entities/ItemEntity.h"
#include "Entities/EntityColiseum.h"
#include "Topography/LocalMap.h"
#include "GraphicsThings/ColorMap.h"
#include "Topography/TileCoordinates.h"


class ItemFactory {
private:
   EntityColiseum<ItemEntity>* coliseum;
   LocalMap* map;

   ColorMap colorMap;
   
   void registerItem(ItemEntity* item, TileCoords location);

public:
   ItemFactory(EntityColiseum<ItemEntity>* coliseum, LocalMap* map) :
   coliseum(coliseum), map(map) {};

   ItemEntity* makeBasicSword(TileCoords location);
   ItemEntity* makeIntelligenceMushroom(TileCoords location);
   ItemEntity* makeStrengthFruit(TileCoords location);
};

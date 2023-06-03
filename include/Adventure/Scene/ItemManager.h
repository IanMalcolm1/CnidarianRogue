#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/Items/ItemEntity.h"
#include "Entities/Items/ItemFactory.h"
#include "Logs/GameLog.h"
#include "Topography/LocalMap.h"
#include "Topography/TileCoordinates.h"


class ItemManager {
private:
   EntityColiseum<ItemEntity> itemColiseum;

   LocalMap* map;

public:
   ItemManager() : map(nullptr) {};

   void initialize(LocalMap* map);
   void initializeFactory(ItemFactory* itemFactory);

   ItemEntity* getItem(int id);

   void destroyItem(ItemEntity* item);
   void moveItem(ItemEntity* item, TileCoords location);
};

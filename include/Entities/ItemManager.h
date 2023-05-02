#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/ItemEntity.h"
#include "Entities/ItemFactory.h"
#include "Logs/GameLog.h"
#include "Topography/LocalMap.h"


class ItemManager {
private:
   EntityColiseum<ItemEntity> itemColiseum;

   LocalMap* map;

public:
   ItemManager(LocalMap* map) : map(map),
   itemColiseum(EntityColiseum<ItemEntity>()) {};

   ItemFactory makeFactory();

   ItemEntity* getItem(int id);

   void destroyItem(ItemEntity* item);
};

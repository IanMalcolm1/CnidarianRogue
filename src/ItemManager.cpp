#include "Adventure/Scene/ItemManager.h"


ItemFactory ItemManager::makeFactory() {
   return ItemFactory(&itemColiseum, map);
}

ItemEntity* ItemManager::getItem(int id) {
   return itemColiseum.getEntity(id);
}

void ItemManager::destroyItem(ItemEntity* item) {
   if (item->location != TileCoords(-1,-1)) {
      map->removeItemAt(item->location, item);
   }
   itemColiseum.deleteEntity(item->getId());
}

void ItemManager::moveItem(ItemEntity* item, TileCoords location) {
   if (item->location != TileCoords(-1,-1)) {
      map->removeItemAt(item->location, item);
   }

   item->location = location;

   if (item->location != TileCoords(-1,-1)) {
      map->addItemAt(location, item);
   }
}

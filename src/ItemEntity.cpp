#include "Entities/Items/ItemEntity.h"
#include "Topography/TileCoordinates.h"


void ItemEntity::reset() {
   display = EntityDisplay();
   description.name = "destroyed entity";
   description.desc = "if you can see this there's a bug";
   location = TileCoords();

   Entity::reset();
}

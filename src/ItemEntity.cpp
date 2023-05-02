#include "Entities/ItemEntity.h"
#include "Topography/TileCoordinates.h"


void ItemEntity::reset() {
   display = TileDisplay();
   description.name = "destroyed entity";
   description.desc = "if you can see this there's a bug";
   location = TileCoords();

   Entity::reset();
}

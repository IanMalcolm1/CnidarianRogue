#pragma once

#include "Entities/Entity.h"
#include "Topography/TileCoordinates.h"


class ItemEntity : public Entity {
private:

public:
   TileCoords location;
   TileDisplay display;
   Description description;


   ItemEntity(int id, int bytesUsed, int totalSpace) :
   Entity(id, bytesUsed, totalSpace), display(), description() {};


   void reset();
};

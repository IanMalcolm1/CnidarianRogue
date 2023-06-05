#pragma once

#include "Topography/LocalMap.h"
#include <string>


class TerrainDescriber {
private:
   LocalMap* map;

public:
   void setMap(LocalMap* map);

   std::string describeTerrainAt(TileCoords location);
};

#include "Topography/TerrainDescriber.h"
#include "GraphicsThings/TileDisplay.h"


void TerrainDescriber::setMap(LocalMap *map) {
   this->map = map;
}


std::string TerrainDescriber::describeTerrainAt(TileCoords location) {
   std::string name = map->getTerrainNameAt(location);
   TileDisplay disp = map->getTerrainDisplayAt(location);

   name.insert(0, "\\> ");
   name.insert(0, std::string(1, (char)disp.symbol));
   name.insert(0, ":");

   std::string color = std::to_string(disp.symbolColor.b);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);

   color = std::to_string(disp.symbolColor.g);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);
   
   color = std::to_string(disp.symbolColor.r);
   if (color.size() < 3) { color.insert(0, "0"); }
   if (color.size() < 3) { color.insert(0, "0"); }
   name.insert(0, color);

   name.insert(0, "</");

   return name;
}

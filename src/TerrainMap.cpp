#include "Topography/TerrainMap.h"


void TerrainMap::setTile(int id, TerrainTile& terrain) {
	displays[id] = terrain.display;
	opacities[id] = terrain.isOpaque;
	traversibilities[id] = terrain.isTraversible;
   types[id] = terrain.type;
   nameIndices[id] = terrain.nameId;
}

TileDisplay TerrainMap::getDisplayAtIndex(int id) { return displays[id]; }
bool TerrainMap::isTraversibleAtIndex(int id) { return traversibilities[id]; }
bool TerrainMap::isOpaqueAtIndex(int id) { return opacities[id]; }
TerrainType TerrainMap::getTerrainTypeAtIndex(int index) { return types[index]; }
std::string TerrainMap::getNameAt(int index) {
   return nameCatalogue.getName(nameIndices[index]);
}
TerrainTile TerrainMap::getTileAt(int i) {
   return TerrainTile(types[i], nameIndices[i], displays[i], traversibilities[i], opacities[i]);
}

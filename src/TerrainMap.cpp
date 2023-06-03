#include "Topography/TerrainMap.h"


void TerrainMap::setTile(int id, TerrainTile& terrain) {
	displays[id] = terrain.display;
	opacities[id] = terrain.isOpaque;
	traversibilities[id] = terrain.isTraversible;
}

TileDisplay TerrainMap::getDisplayAtIndex(int id) { return displays[id]; }
bool TerrainMap::isTraversibleAtIndex(int id) { return traversibilities[id]; }
bool TerrainMap::isOpaqueAtIndex(int id) { return opacities[id]; }

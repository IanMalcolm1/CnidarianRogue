#include "Topography/TerrainMap.h"


void TerrainMap::setTile(int id, TileDisplay display, bool traversible, bool opaque) {
	displays[id] = display;
	opacities[id] = opaque;
	traversibilities[id] = traversible;
}

TileDisplay TerrainMap::getDisplayAtIndex(int id) { return displays[id]; }
bool TerrainMap::isTraversibleAtIndex(int id) { return traversibilities[id]; }
bool TerrainMap::isOpaqueAtIndex(int id) { return opacities[id]; }

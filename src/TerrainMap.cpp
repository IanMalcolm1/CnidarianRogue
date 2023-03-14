#include "Topography/TerrainMap.h"

TerrainMap::TerrainMap(int width, int height) {
	_displays = std::make_unique<TileDisplay[]>(width * height);
	_traversibilities = std::make_unique<bool[]>(width * height);
	_opacities = std::make_unique<bool[]>(width * height);
}


void TerrainMap::setTile(int id, TileDisplay* display, bool traversible, bool opaque) {
	_displays[id].copy(display);
	_opacities[id] = opaque;
	_traversibilities[id] = traversible;
}


TileDisplay* TerrainMap::getDisplayAtIndex(int id) { return &_displays[id]; }
bool TerrainMap::isTraversibleAtIndex(int id) { return _traversibilities[id]; }
bool TerrainMap::isOpaqueAtIndex(int id) { return _opacities[id]; }

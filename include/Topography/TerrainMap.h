#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include "GraphicsThings/TileDisplay.h"
#include <vector>


class TerrainMap {
private:
   std::vector<TileDisplay> displays;
	std::vector<bool> traversibilities;
	std::vector<bool> opacities;

public:
	TerrainMap(int width, int height) : displays(width*height),
   traversibilities(width*height), opacities(width*height) {};

	void setTile(int index, TileDisplay display, bool traversible, bool opaque);

	TileDisplay getDisplayAtIndex(int index);

	bool isTraversibleAtIndex(int index);

	bool isOpaqueAtIndex(int index);
};

#endif

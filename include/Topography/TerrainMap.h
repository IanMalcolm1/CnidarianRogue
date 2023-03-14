#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include "GraphicsThings/TileDisplay.h"
#include <memory>


class TerrainMap {
private:

	std::unique_ptr<TileDisplay[]> _displays;
	std::unique_ptr<bool[]> _traversibilities;
	std::unique_ptr<bool[]> _opacities;

public:
	TerrainMap(int width, int height);

	void setTile(int index, TileDisplay* display, bool traversible, bool opaque);

	TileDisplay* getDisplayAtIndex(int index);

	bool isTraversibleAtIndex(int index);

	bool isOpaqueAtIndex(int index);
};

#endif

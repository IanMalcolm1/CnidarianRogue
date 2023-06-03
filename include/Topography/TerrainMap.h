#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include "GraphicsThings/TileDisplay.h"
#include <vector>

enum TerrainType {
   TERRAIN_NORMAL,
   TERRAIN_UPSTAIRS,
   TERRAIN_DOWNSTAIRS,
};

struct TerrainTile {
   TerrainType type;
   TileDisplay display;
   bool isTraversible;
   bool isOpaque;

   TerrainTile(TerrainType type, TileDisplay display, bool traversible, bool opaque) :
   type(type), display(display), isTraversible(traversible), isOpaque(opaque) {};
};

class TerrainMap {
private:
   std::vector<TileDisplay> displays;
	std::vector<bool> traversibilities;
	std::vector<bool> opacities;
   std::vector<TerrainType> types;

public:
	TerrainMap(int width, int height) : displays(width*height),
   traversibilities(width*height), opacities(width*height),
   types(width*height) {};

	void setTile(int index, TerrainTile& terrain);

	TileDisplay getDisplayAtIndex(int index);
	bool isTraversibleAtIndex(int index);
	bool isOpaqueAtIndex(int index);
   TerrainType getTerrainTypeAtIndex(int index);
};

#endif

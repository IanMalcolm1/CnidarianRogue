#ifndef TERRAINMAP_H
#define TERRAINMAP_H

#include "GraphicsThings/TileDisplay.h"
#include "Topography/TerrainNameCatalogue.h"
#include <vector>

enum TerrainType {
   TERRAIN_NORMAL,
   TERRAIN_UPSTAIRS,
   TERRAIN_DOWNSTAIRS,
};

struct TerrainTile {
   int nameId;
   TerrainType type;
   TileDisplay display;
   bool isTraversible;
   bool isOpaque;

   TerrainTile(TerrainType type = TERRAIN_NORMAL, int nameId = -1,
   TileDisplay display = TileDisplay(), bool traversible = false,
   bool opaque = false) : type(type), display(display),
   isTraversible(traversible), isOpaque(opaque), nameId(nameId) {};

   bool operator == (const TerrainTile tile) const {
      return (nameId==tile.nameId && type==tile.type && display.symbol==tile.display.symbol && isTraversible==tile.isTraversible && isOpaque==tile.isOpaque);
   }

   bool operator != (const TerrainTile tile) const {
      return !((*this)==tile);
   }
};

class TerrainMap {
private:
   TerrainNameCatalogue nameCatalogue;

   std::vector<TileDisplay> displays;
	std::vector<bool> traversibilities;
	std::vector<bool> opacities;
   std::vector<TerrainType> types;
   std::vector<int> nameIndices;

public:
	TerrainMap(int width, int height) : displays(width*height),
   traversibilities(width*height), opacities(width*height),
   types(width*height), nameIndices(width*height) {};

	void setTile(int index, TerrainTile& terrain);

	TileDisplay getDisplayAtIndex(int index);
	bool isTraversibleAtIndex(int index);
	bool isOpaqueAtIndex(int index);
   TerrainType getTerrainTypeAtIndex(int index);
   std::string getNameAt(int index);
   TerrainTile getTileAt(int index);

   int addName(std::string name) {
      return nameCatalogue.addName(name);
   }
};

#endif

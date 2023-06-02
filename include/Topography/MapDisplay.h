#pragma once

//?:#include <>
#include <vector>
#include "GraphicsThings/TileDisplay.h"
#include "Topography/TileCoordinates.h"


struct MapDisplayTile {
	TileDisplay display;
	bool isVisible;
	bool hasBeenSeen;
	bool hasReticle;
};


/* Struct for buffer arrays */
class MapDisplay {
private:
	int width, height;

	TileCoords focusTile;

	std::vector<MapDisplayTile> tiles;
   std::vector<std::vector<int>> dirtyTiles;

   void setDirty(int index);

public:
	MapDisplay(int width, int height) : width(width), height(height),
   focusTile({ 0,0 }), tiles(width* height, { false, false, false }),
   dirtyTiles(height) {};
	~MapDisplay();

	int getWidth();
	int getHeight();

   std::vector<int>* getDirtyTilesRow(int row);

	TileDisplay* getDisplayAt(int index);
	void setDisplayAt(int index, TileDisplay display);

	TileCoords getFocusTile();
	void setFocusTile(TileCoords tile);

	bool isVisible(int index);
	bool hasBeenSeen(int index);
	bool hasReticle(int index);

	void setVisibility(int index, bool value);
	void setHasReticle(int index, bool value);
};

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
   std::vector<int> dirtyTiles;

public:
	MapDisplay(int width, int height) : width(width), height(height),
   focusTile({ 0,0 }), tiles(width* height, { false, false, false }),
   dirtyTiles(width*height/2) {};
	~MapDisplay();

	int getWidth();
	int getHeight();

   std::vector<int>* getDirtyTiles();

	TileDisplay* getDisplayAt(int index);
	void setDisplayAt(int index, TileDisplay display);

	TileCoords getFocusTile();
	void setFocusTile(TileCoords tile);

	bool isVisible(int index);
	bool hasBeenSeen(int index);
	bool hasReticle(int index);

	void setVisibility(int index, bool value);
	void setHasReticle(int index, bool value);

	void setDirty(int index);
};

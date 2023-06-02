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
	bool dirty;
};


/* Struct for buffer arrays */
class MapDisplay {
private:
	int width, height;

	TileCoords focusTile;

	std::vector<MapDisplayTile> tiles;

public:
	MapDisplay(int width, int height) : width(width), height(height), focusTile({ 0,0 }),
		tiles(width* height, { false, false, false }) {};
	~MapDisplay();

	int getWidth();
	int getHeight();

	TileDisplay* getDisplay(int index);
	void setDisplayAt(int index, TileDisplay display);

	TileCoords getFocusTile();
	void setFocusTile(TileCoords tile);

	bool isVisible(int index);
	bool hasBeenSeen(int index);
	bool hasReticle(int index);

	void setVisibility(int index, bool value);
	void setHasReticle(int index, bool value);

	bool isDirty(int index);
	inline void setDirty(int index, bool value) { tiles[index].dirty = value; }
};

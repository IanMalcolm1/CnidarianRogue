#include "Topography/MapDisplay.h"
#include <cstdio>

MapDisplay::~MapDisplay() {
	printf("Buffer map destructor called\n");
}

int MapDisplay::getWidth() { return width; }
int MapDisplay::getHeight() { return height; }

std::vector<int>* MapDisplay::getDirtyTilesRow(int row) {
   return &dirtyTiles[row];
}

TileDisplay* MapDisplay::getDisplayAt(int index) { return &tiles[index].display; }
void MapDisplay::setDisplayAt(int index, TileDisplay display) {
	tiles[index].display = display;
	setDirty(index);
}

TileCoords MapDisplay::getFocusTile() { return focusTile; }
void MapDisplay::setFocusTile(TileCoords tile) {
   tiles[focusTile.y*width + focusTile.x].hasReticle = false;
   focusTile = tile;
}

bool MapDisplay::isVisible(int index) { return tiles[index].isVisible; }
bool MapDisplay::hasBeenSeen(int index) { return tiles[index].hasBeenSeen; }
bool MapDisplay::hasReticle(int index) { return tiles[index].hasReticle; }

void MapDisplay::setVisibility(int index, bool value) { 
	tiles[index].isVisible = value; 
   if (value == true) {
	   tiles[index].hasBeenSeen = value;
   };
	setDirty(index);
}
void MapDisplay::setHasReticle(int index, bool value) {
	tiles[index].hasReticle = value;
	setDirty(index);
}

void MapDisplay::setDirty(int index) {
   dirtyTiles[index/width].push_back(index);
}

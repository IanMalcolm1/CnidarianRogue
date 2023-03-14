#include "Topography/MapDisplay.h"
#include <cstdio>

MapDisplay::~MapDisplay() {
	printf("Buffer map destructor called\n");
}

int MapDisplay::getWidth() { return width; }
int MapDisplay::getHeight() { return height; }

TileDisplay* MapDisplay::getDisplay(int index) { return &tiles[index].display; }
void MapDisplay::setDisplayAt(int index, TileDisplay* display) {
	tiles[index].display.copy(display);
	setDirty(index, true);
}

TileCoords MapDisplay::getFocusTile() { return focusTile; }
void MapDisplay::setFocusTile(TileCoords tile) { focusTile = tile; }

bool MapDisplay::isVisible(int index) { return tiles[index].isVisible; }
bool MapDisplay::hasBeenSeen(int index) { return tiles[index].hasBeenSeen; }
bool MapDisplay::hasReticle(int index) { return tiles[index].hasReticle; }

void MapDisplay::setVisibility(int index, bool value) { 
	tiles[index].isVisible = value; 
	setDirty(index, true);
}
void MapDisplay::setSeen(int index, bool value) {
	tiles[index].hasBeenSeen = value;
	setDirty(index, true);
}
void MapDisplay::setHasReticle(int index, bool value) {
	tiles[index].hasReticle = value;
	setDirty(index, true);
}

bool MapDisplay::isDirty(int index) { return tiles[index].dirty; }

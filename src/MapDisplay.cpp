#include "Topography/MapDisplay.h"
#include <cstdio>

MapDisplay::~MapDisplay() {
	printf("Buffer map destructor called\n");
}

int MapDisplay::getWidth() { return width; }
int MapDisplay::getHeight() { return height; }

bool MapDisplay::rowIsEmpty(int row) {
   return dirtyTiles[row].empty();
}

int MapDisplay::getNextIndexFromRow(int row) {
   int index = dirtyTiles[row].back();
   dirtyTiles[row].pop_back();
   isDirtyLookup[index] = false;

   return index;
}

TileDisplay* MapDisplay::getDisplayAt(int index) { return &tiles[index].display; }
void MapDisplay::setDisplayAt(int index, TileDisplay display) {
   if (display == tiles[index].display) {
      return;
   }

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

void MapDisplay::resetVisibility(int index) {
   visibilityWasResetLookup[index] = true;
   visibilityResetIndices.push_back(index);
}

void MapDisplay::setVisible(int index) { 
   if (visibilityWasResetLookup[index] == true) { //if undoing visibility reset
      visibilityWasResetLookup[index] = false;
      return;
   }

	tiles[index].isVisible = true; 
	tiles[index].hasBeenSeen = true;

	setDirty(index);
}

void MapDisplay::resetVisibilityResets() {
   for (int index : visibilityResetIndices) {
      if (visibilityWasResetLookup[index] == true) {
         tiles[index].isVisible = false;
         setDirty(index);
      }
      visibilityWasResetLookup[index] = false;
   }

   visibilityResetIndices.clear();
}

void MapDisplay::setHasReticle(int index, bool value) {
	tiles[index].hasReticle = value;
	setDirty(index);
}

void MapDisplay::setDirty(int index) {
   if (isDirtyLookup[index] == false) {
      isDirtyLookup[index] = true;
      dirtyTiles[index/width].push_back(index);
   }
}

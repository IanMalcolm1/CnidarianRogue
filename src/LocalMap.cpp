#include "Topography/LocalMap.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Logs/DebugLogger.h"


/* Graphics */

MapDisplay* LocalMap::getMapDisplay() {
	return &mapDisplay;
}


void LocalMap::updateMapDisplay() {
	if (needToUpdateDisplay) {
		resetVisibleTileDisplays();

		FoV::calcPlayerFoV(this, playerTile);

		updateVisibleTileDisplays();
	}

	updateHighlightedTiles();

	needToUpdateDisplay = false;
}


void LocalMap::updateHighlightedTiles() {
	pathToMouseTile.resetProgress();
	while (pathToMouseTile.hasNextTile()) {
		TileCoords tile = pathToMouseTile.getNextTile();
		setHasReticle(tile, false);
		pathToMouseTile.incrementProgress();
	}

	if (mouseTile.x == -1 || mouseTile.y == -1) {
		return;
	}

	Pathfinding::calcPlayerPathingRoute(playerTile, mouseTile, this, &pathToMouseTile);

	while (pathToMouseTile.hasNextTile()) {
		TileCoords tile = pathToMouseTile.getNextTile();
		setHasReticle(tile, true);
		pathToMouseTile.incrementProgress();
	}

   if (isLooking) {
      setHasReticle(mapDisplay.getFocusTile(), true);
   }
}


void LocalMap::makeVisible(TileCoords location) {
	if (!isInMapBounds(location)) {
      DebugLogger::log("setVisible() coordinates out of bounds");
		return;
	}

	int index = coordsToTileIndex(location);

	mapDisplay.setVisibility(index, true);
	mapDisplay.setSeen(index, true);

	visibleIndices.push_back(index);
}


void LocalMap::resetVisibleTileDisplays() {
	for (int index : visibleIndices) {
		mapDisplay.setVisibility(index, false);

		//reset to view of terrain
		mapDisplay.setDisplayAt(index, terrainMap.getDisplayAtIndex(index));
	}

	visibleIndices.clear();
}


void LocalMap::updateVisibleTileDisplays() {
	for (int index : visibleIndices) {
		mapDisplay.setDisplayAt(index, getDisplayAt(index));
	}
}


void LocalMap::setMouseTile(TileCoords location) {
	mouseTile = location;
}


PathingRoute LocalMap::getRouteToMouseTile() {
	return pathToMouseTile;
}


void LocalMap::flagNeedToUpdateDisplay() {
	needToUpdateDisplay = true;
}


TileDisplay* LocalMap::getDisplayAt(int index) {
	if (actors[index] != nullptr) {
		ActorEntity* test = actors[index];
		return &actors[index]->display;
	}

	if (items[index].size() > 0) {
		return &items[index][0]->display;
	}

	return terrainMap.getDisplayAtIndex(index);
}
TileDisplay* LocalMap::getDisplayAt(TileCoords location) {
	return getDisplayAt(coordsToTileIndex(location));
}

void LocalMap::setDisplayAt(int index, TileDisplay* display) {
	mapDisplay.setDisplayAt(index, display);
}
void LocalMap::setDisplayAt(TileCoords location, TileDisplay* display) {
	mapDisplay.setDisplayAt(coordsToTileIndex(location), display);
}


bool LocalMap::hasReticle(int index) { return mapDisplay.hasReticle(index); }
bool LocalMap::hasReticle(TileCoords tile) { return mapDisplay.hasReticle(coordsToTileIndex(tile)); }

void LocalMap::setHasReticle(int index, bool value) { mapDisplay.setHasReticle(index, value); }
void LocalMap::setHasReticle(TileCoords tile, bool value) {
	mapDisplay.setHasReticle(coordsToTileIndex(tile), value);
}


bool LocalMap::hasBeenSeen(TileCoords location) {
	return mapDisplay.hasBeenSeen(coordsToTileIndex(location));
}





/* Manipulation */

void LocalMap::setPlayerLocation(ActorEntity* player, TileCoords newLocation) {
	if (player->location.x != -1) {
		actors[coordsToTileIndex(player->location)] = nullptr;
	}

	player->location = newLocation;

	playerTile = newLocation;
	
	actors[coordsToTileIndex(newLocation)] = player;
	mapDisplay.setFocusTile(newLocation);
}

TileCoords LocalMap::getFocusTileLocation() {
	return mapDisplay.getFocusTile();
}

void LocalMap::setFocusTileLocation(TileCoords location) {
	mapDisplay.setFocusTile(location);
}

void LocalMap::stopLooking() {
	setHasReticle(mapDisplay.getFocusTile(), false);
	mapDisplay.setFocusTile(playerTile);
   isLooking = false;
}

void LocalMap::setLookTile(TileCoords newCoords) {
	setHasReticle(getFocusTileLocation(), false);
	setHasReticle(newCoords, true);
	mapDisplay.setFocusTile(newCoords);
   isLooking = true;
}

void LocalMap::lookAtMouseTile() {
   setLookTile(mouseTile);
}


bool LocalMap::isInMapBounds(TileCoords location) {
	return (location.x>-1 && location.y>-1 && location.x<width && location.y<height);
}

void LocalMap::setTerrainAt(int index, TileDisplay* display, bool traversible, bool opaque) {
	terrainMap.setTile(index, display, traversible, opaque);
}
void LocalMap::setTerrainAt(TileCoords location, TileDisplay* display, bool traversible, bool opaque) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("setTerrainAt() coordinates out of bounds");
		return;
	}
	setTerrainAt(coordsToTileIndex(location), display, traversible, opaque);
}

bool LocalMap::isTraversibleAt(int index) {
	return (terrainMap.isTraversibleAtIndex(index) && actors[index]==nullptr);
}
bool LocalMap::isTraversibleAt(TileCoords location) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("isTraversibleAt() coordinates out of bounds");
		return false;
	}
	return isTraversibleAt(coordsToTileIndex(location));
}

bool LocalMap::isOpaqueAt(int index) { return terrainMap.isOpaqueAtIndex(index); }
bool LocalMap::isOpaqueAt(TileCoords location) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("isOpaqueAt() coordinates out of bounds");
		return false;
	}
	return terrainMap.isOpaqueAtIndex(coordsToTileIndex(location));
}


bool LocalMap::thereIsAnActorAt(int index) { return actors[index] != nullptr; }
bool LocalMap::thereIsAnActorAt(TileCoords location) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("thereIsAnActorAt() coordinates out of bounds");
		return false;
	}
	return actors[coordsToTileIndex(location)] != nullptr;
}


ActorEntity* LocalMap::getActorAt(int index) { return actors[index]; }
ActorEntity* LocalMap::getActorAt(TileCoords location) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("getActorAt() coordinates out of bounds");
		return nullptr;
	}
	return getActorAt( coordsToTileIndex(location) );
}


void LocalMap::setActorAt(int index, ActorEntity* actor) { actors[index] = actor; }
void LocalMap::setActorAt(TileCoords location, ActorEntity* actor) {
	if (!isInMapBounds(location)) {
		DebugLogger::log("setActorAt() coordinates out of bounds");
		return;
	}
	setActorAt(coordsToTileIndex(location), actor);
}


std::vector<ItemEntity*>* LocalMap::getItemsAt(int index) {
   return &items[index];
}
std::vector<ItemEntity*>* LocalMap::getItemsAt(TileCoords coords) {
   if (!isInMapBounds(coords)) {
      DebugLogger::log("getItemsAt() out of bounds");
      return nullptr;
   }
   return getItemsAt(coordsToTileIndex(coords));
}   


void LocalMap::addItemAt(int index, ItemEntity* item) {
   if (item) {
      items[index].push_back(item);
   }
}
void LocalMap::addItemAt(TileCoords coords, ItemEntity* item) {
   if (!isInMapBounds(coords)) {
      DebugLogger::log("addItemAt() out of bounds");
      return;
   }
   return addItemAt(coordsToTileIndex(coords), item);
}


void LocalMap::removeItemAt(int index, ItemEntity* item) {
   for (int i=0; i<items[index].size(); i++) {
      if (items[index][i] == item) {
         items[index].erase(items[index].begin() + i);
      }
   }
}
void LocalMap::removeItemAt(TileCoords coords, ItemEntity* item) {
   if (!isInMapBounds(coords)) {
      DebugLogger::log("removeItemAt() out of bounds");
      return;
   }
   removeItemAt(coordsToTileIndex(coords), item);
}




/* Utilities */

int LocalMap::getWidth() { return width; }
int LocalMap::getHeight() { return height; }


int LocalMap::coordsToTileIndex(TileCoords coordinates) {
	if (coordinates.x < 0 || coordinates.y < 0 || coordinates.x >= width || coordinates.x >= height) {
		DebugLogger::log("Coords to tile ID out of bounds");
		return -1;
	}

	return coordinates.y * width + coordinates.x;
}

TileCoords LocalMap::tileIndexToCoords(int index) {
	TileCoords coordinates;

	if (index <0 || index>width * height) {
		coordinates.x = coordinates.y = -1;
		return coordinates;
	}

	coordinates.x = index % width;
	coordinates.y = index / width;
	return coordinates;
}


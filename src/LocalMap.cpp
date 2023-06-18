#include "Topography/LocalMap.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathingSpecs.h"
#include "Logs/DebugLogger.h"
#include "Topography/TerrainMap.h"
#include <climits>



/* Graphics */

MapDisplay* LocalMap::getMapDisplay() {
   return &mapDisplay;
}


void LocalMap::updateMapDisplay() {
   if (needToUpdateDisplay) {
      updateVisibleTileDisplays();
   }

   updateHighlightedTiles();

   needToUpdateDisplay = false;
}


void LocalMap::updateHighlightedTiles() {
   unhighlightPathToMouseTile();

   makeHighlightRoute();

   highlightPathToMouseTile();

   if (isLooking) {
      setHasReticle(mapDisplay.getFocusTile(), true);
   }
}

void LocalMap::highlightPathToMouseTile() {
   pathToMouseTile.resetProgress();

   while (pathToMouseTile.hasNextTile()) {
      TileCoords tile = pathToMouseTile.getNextTile();
      setHasReticle(tile, true);
      pathToMouseTile.incrementProgress();
   }
}

void LocalMap::unhighlightPathToMouseTile() {
   pathToMouseTile.resetProgress();

   while (pathToMouseTile.hasNextTile()) {
      TileCoords tile = pathToMouseTile.getNextTile();
      setHasReticle(tile, false);
      pathToMouseTile.incrementProgress();
   }
}

void LocalMap::makeVisible(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("setVisible() coordinates out of bounds");
      return;
   }

   int index = coordsToTileIndex(location);

   mapDisplay.setVisible(index);

   visibleIndices.push_back(index);
}


void LocalMap::resetVisibleTileDisplays() {
   for (int index : visibleIndices) {
      mapDisplay.resetVisibility(index);

      //reset to view of terrain
      mapDisplay.setDisplayAt(index, terrainMap.getDisplayAtIndex(index));
   }

   visibleIndices.clear();
}


void LocalMap::updateVisibleTileDisplays() {
   //normal state of affairs
   for (int index : visibleIndices) {
      mapDisplay.setDisplayAt(index, getDisplayAt(index));
   }

   mapDisplay.resetVisibilityResets();

   //set everything visible
   /*
   for (int i=0; i<width*height; i++) {
      mapDisplay.setDisplayAt(i, getDisplayAt(i));
      mapDisplay.setVisible(i);
   }
   */
}


void LocalMap::setMouseTile(TileCoords location) {
   mouseTile = location;
}

void LocalMap::flagMouseMoved() {
   if (isInMapBounds(mouseTile)) {
      focusTileChangedLast = false;
   }
}


void LocalMap::makeHighlightRoute() {
   unhighlightPathToMouseTile();

   pathToMouseTile.clear();
   pathingSpecs.start = playerTile;

   if (pathingSpecs.type == PATH_ROUTE) {
      pathingSpecs.end = mouseTile;
      pathingSpecs.routeInfo.maxAStarTiles = INT_MAX;
   }

   else if (pathingSpecs.type == PATH_LINE) {
      if (focusTileChangedLast) {
         pathingSpecs.end = mapDisplay.getFocusTile();
      }
      else  {
         pathingSpecs.end = mouseTile;
      }
   }

   if (!isInMapBounds(pathingSpecs.start) || !isInMapBounds(pathingSpecs.end)) {
      return;
   }

   Pathfinding::calcPath(pathingSpecs, this, pathToMouseTile);
}

void LocalMap::setHighlightRouteSpecs(PathingSpecs specs) {
   pathingSpecs = specs;
}

TileCoords LocalMap::getTargetTile() {
   if (focusTileChangedLast) {
      return mapDisplay.getFocusTile();
   }
   else {
      return mouseTile;
   }
}

PathingRoute LocalMap::getHighlightedPath() {
   pathToMouseTile.resetProgress();
   return pathToMouseTile;
}


void LocalMap::flagNeedToUpdateDisplay() {
   needToUpdateDisplay = true;
}


TileDisplay LocalMap::getDisplayAt(int index) {
   if (actors[index] != nullptr) {
      return TileDisplay(actors[index]->display, terrainMap.getDisplayAtIndex(index).backColor);
   }

   if (items[index].size() > 0) {
      return TileDisplay(items[index][0]->display, terrainMap.getDisplayAtIndex(index).backColor);
   }

   return terrainMap.getDisplayAtIndex(index);
}
TileDisplay LocalMap::getDisplayAt(TileCoords location) {
   return getDisplayAt(coordsToTileIndex(location));
}

void LocalMap::setDisplayAt(int index, TileDisplay display) {
   mapDisplay.setDisplayAt(index, display);
}
void LocalMap::setDisplayAt(TileCoords location, TileDisplay display) {
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
bool LocalMap::isTraversibleAndSeen(TileCoords location) {
   return isTraversibleAt(location) && hasBeenSeen(location);
}





/* Manipulation */

void LocalMap::setPlayerLocation(ActorEntity* player, TileCoords newLocation) {
   if (player->location.x != -1) {
      setActorAt(player->location, nullptr);
   }

   player->location = newLocation;

   playerTile = newLocation;

   setActorAt(newLocation, player);
   mapDisplay.setFocusTile(newLocation);
}

TileCoords LocalMap::getFocusTileLocation() {
   return mapDisplay.getFocusTile();
}

void LocalMap::setFocusTileLocation(TileCoords location) {
   mapDisplay.setFocusTile(location);
   focusTileChangedLast = true;
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
   focusTileChangedLast = true;
}

void LocalMap::lookAtMouseTile() {
   setLookTile(mouseTile);
}


bool LocalMap::isInMapBounds(TileCoords location) {
   return (location.x>-1 && location.y>-1 && location.x<width && location.y<height);
}

void LocalMap::setTerrainAt(int index, TerrainTile& terrain) {
   terrainMap.setTile(index, terrain);
}
void LocalMap::setTerrainAt(TileCoords location, TerrainTile& terrain) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("setTerrainAt() coordinates out of bounds");
      return;
   }
   setTerrainAt(coordsToTileIndex(location), terrain);
}

TerrainTile LocalMap::getTerrainAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("getTerrainAt() coordinates out of bounds");
      return TerrainTile();
   }
   return terrainMap.getTileAt(coordsToTileIndex(location));
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

bool LocalMap::isPenetratableAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("isPenetratableAt() coordinates out of bounds");
      return false;
   }
   return terrainMap.isTraversibleAtIndex(coordsToTileIndex(location));
}

bool LocalMap::isOpaqueAt(int index) { return terrainMap.isOpaqueAtIndex(index); }
bool LocalMap::isOpaqueAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("isOpaqueAt() coordinates out of bounds");
      return false;
   }
   return terrainMap.isOpaqueAtIndex(coordsToTileIndex(location));
}

TerrainType LocalMap::getTerrainTypeAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("getTerrainTypeAt() coordinates out of bounds");
      return TERRAIN_NORMAL;
   }
   return terrainMap.getTerrainTypeAtIndex(coordsToTileIndex(location));
}

int LocalMap::addTerrainName(std::string name) {
   return terrainMap.addName(name);
}

std::string LocalMap::getTerrainNameAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("getTerrainNameAt() coordinates out of bounds");
      return "Out of bounds";
   }
   return terrainMap.getNameAt(coordsToTileIndex(location));
}

TileDisplay LocalMap::getTerrainDisplayAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("getTerrainDisplayAt() coordinates out of bounds");
      return TileDisplay();
   }
   return terrainMap.getDisplayAtIndex(coordsToTileIndex(location));
}

bool LocalMap::isVisibleAt(TileCoords location) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("isVisibleAt() coordinates out of bounds");
      return false;
   }
   return mapDisplay.isVisible(coordsToTileIndex(location));
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


void LocalMap::setActorAt(TileCoords location, ActorEntity* actor) {
   if (!isInMapBounds(location)) {
      DebugLogger::log("setActorAt() coordinates out of bounds");
      return;
   }
   actors[coordsToTileIndex(location)] = actor;
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


std::vector<TileCoords> LocalMap::getSurroundingTiles(TileCoords center) {
	std::vector<TileCoords> tiles;

	center.x++;
	tiles.push_back(center);
	center.y++;
	tiles.push_back(center);
	center.x--;
	tiles.push_back(center);
	center.x--;
	tiles.push_back(center);
	center.y--;
	tiles.push_back(center);
	center.y--;
	tiles.push_back(center);
	center.x++;
	tiles.push_back(center);
	center.x++;
	tiles.push_back(center);

	return tiles;
}

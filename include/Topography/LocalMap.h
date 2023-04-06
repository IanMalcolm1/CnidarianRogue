#ifndef LOCALMAP_H
#define LOCALMAP_H


#include "TerrainMap.h"
#include "MapDisplay.h"
#include "Entities/ActorEntity.h"
#include "Entities/ItemEntity.h"
#include "Enums/PlayerCommands.h"
#include "Algorithms/PathfindingRoute.h"
#include "Logs/DebugLogger.h"


/* Class for Local Maps */
class LocalMap {
private:
	int width;
	int height;

	TileCoords mouseTile;
	TileCoords playerTile;

	DebugLogger debugLogger;

	PathingRoute pathToMouseTile;

	MapDisplay mapDisplay;
	std::vector<int16_t> visibleIndices;
	bool needToUpdateDisplay;

	TerrainMap terrainMap;

	std::vector<ActorEntity*> actors;
	std::vector<std::vector<ItemEntity*>> items;

	void updateHighlightedTiles();

	void resetVisibleTileDisplays();
	void updateVisibleTileDisplays();

	TileDisplay* getDisplayAt(int index);
	TileDisplay* getDisplayAt(TileCoords location);
	void setDisplayAt(int index, TileDisplay* display);
	void setDisplayAt(TileCoords location, TileDisplay* display);

	bool hasReticle(int index);
	bool hasReticle(TileCoords tile);
	void setHasReticle(int index, bool hasReticle);
	void setHasReticle(TileCoords tile, bool hasReticle);

public:
	LocalMap(int width, int height);

	MapDisplay* getMapDisplay();
	void updateMapDisplay();

	int coordsToTileIndex(TileCoords coordinates);
	TileCoords tileIndexToCoords(int index);

	int getWidth();
	int getHeight();

	bool isInMapBounds(TileCoords location);
	void setTerrainAt(int index, TileDisplay* display, bool traversible, bool opaque);
	void setTerrainAt(TileCoords location, TileDisplay* display, bool traversible, bool opaque);
	bool isTraversibleAt(int index);
	bool isTraversibleAt(TileCoords location);
	bool isOpaqueAt(int index);
	bool isOpaqueAt(TileCoords location);
	bool hasBeenSeen(TileCoords location);

	bool thereIsAnActorAt(int index);
	bool thereIsAnActorAt(TileCoords location);
	ActorEntity* getActorAt(int index);
	ActorEntity* getActorAt(TileCoords location);
	void setActorAt(int index, ActorEntity* actor);
	void setActorAt(TileCoords location, ActorEntity* actor);
	void setPlayerLocation(ActorEntity* player, TileCoords newLocation);

	TileCoords getFocusTileLocation();
	void setFocusTileLocation(TileCoords location);
	void stopLooking();
	void setLookTile(TileCoords newCoords);
	void setLookTile(TileCoords oldCoords, TileCoords newCoords);

	void makeVisible(TileCoords location);

	void setMouseTile(TileCoords coordinates);
	PathingRoute getRouteToMouseTile();

	void flagNeedToUpdateDisplay();
};


#endif

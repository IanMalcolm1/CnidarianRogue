#ifndef LOCALMAP_H
#define LOCALMAP_H


#include "GraphicsThings/TileDisplay.h"
#include "Algorithms/PathingSpecs.h"
#include "TerrainMap.h"
#include "MapDisplay.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Items/ItemEntity.h"
#include "Enums/PlayerCommands.h"
#include "Algorithms/PathfindingRoute.h"
#include "Topography/TileCoordinates.h"


/* Should be pretty obvious what this class does. The
 * 'Local' part is just because I was thinking to also
 * have a 'Global' version at one point */
class LocalMap {
private:
	int width;
	int height;

	TileCoords mouseTile;
	TileCoords playerTile;
   bool isLooking;

   PathingSpecs pathingSpecs;
	PathingRoute pathToMouseTile;
   bool focusTileChangedLast; //false = opposite is mouse tile changed last

	MapDisplay mapDisplay;
	std::vector<int> visibleIndices;
	bool needToUpdateDisplay;

	TerrainMap terrainMap;

	std::vector<ActorEntity*> actors;
	std::vector<std::vector<ItemEntity*>> items;

	void updateHighlightedTiles();

	void updateVisibleTileDisplays();

	TileDisplay getDisplayAt(int index);
	TileDisplay getDisplayAt(TileCoords location);
	void setDisplayAt(int index, TileDisplay display);
	void setDisplayAt(TileCoords location, TileDisplay display);

	bool hasReticle(int index);
	bool hasReticle(TileCoords tile);
	void setHasReticle(int index, bool hasReticle);
	void setHasReticle(TileCoords tile, bool hasReticle);

   void highlightPathToMouseTile();
   void unhighlightPathToMouseTile();
   void makeHighlightRoute();

public:
	LocalMap(int width, int height) : mapDisplay(width, height),
	terrainMap(width, height), actors(width*height, nullptr),
	items(width*height, std::vector<ItemEntity*>()), pathToMouseTile(),
   width(width), height(height), needToUpdateDisplay(true), isLooking(false),
   mouseTile(-1,-1), focusTileChangedLast(false),
   pathingSpecs(PATH_ROUTE, TRAV_INCLUDE_UNSEEN_TILES) {};


	MapDisplay* getMapDisplay();
	void updateMapDisplay();
	void resetVisibleTileDisplays();

	int coordsToTileIndex(TileCoords coordinates);
	TileCoords tileIndexToCoords(int index);
   std::vector<TileCoords> getSurroundingTiles(TileCoords center);

	int getWidth();
	int getHeight();

	bool isInMapBounds(TileCoords location);
	void setTerrainAt(int index, TerrainTile& terrain);
	void setTerrainAt(TileCoords location, TerrainTile& terrain);
   TerrainTile getTerrainAt(TileCoords location);
	bool isTraversibleAt(int index);
	bool isTraversibleAt(TileCoords location);
	bool isPenetratableAt(TileCoords location);
	bool isOpaqueAt(int index);
   TerrainType getTerrainTypeAt(TileCoords location);
   int addTerrainName(std::string);
   std::string getTerrainNameAt(TileCoords location);
   TileDisplay getTerrainDisplayAt(TileCoords location);
	bool isOpaqueAt(TileCoords location);
   bool isVisibleAt(TileCoords location);
	bool hasBeenSeen(TileCoords location);
   bool isTraversibleAndSeen(TileCoords location);

	bool thereIsAnActorAt(int index);
	bool thereIsAnActorAt(TileCoords location);
	ActorEntity* getActorAt(int index);
	ActorEntity* getActorAt(TileCoords location);
	void setActorAt(TileCoords location, ActorEntity* actor);
	void setPlayerLocation(ActorEntity* player, TileCoords newLocation);

   std::vector<ItemEntity*>* getItemsAt(int index);
   std::vector<ItemEntity*>* getItemsAt(TileCoords coords);
   void addItemAt(int index, ItemEntity* item);
   void addItemAt(TileCoords coords, ItemEntity* item);
   void removeItemAt(int index, ItemEntity* item);
   void removeItemAt(TileCoords coords, ItemEntity* item);

	TileCoords getFocusTileLocation();
	void setFocusTileLocation(TileCoords location);
	void stopLooking();
	void setLookTile(TileCoords newCoords);
   void lookAtMouseTile();

	void makeVisible(TileCoords location);

	void setMouseTile(TileCoords coordinates);
   void flagMouseMoved();
   void setHighlightRouteSpecs(PathingSpecs specs);
   TileCoords getTargetTile();
   PathingRoute getHighlightedPath();

	void flagNeedToUpdateDisplay();
};


#endif

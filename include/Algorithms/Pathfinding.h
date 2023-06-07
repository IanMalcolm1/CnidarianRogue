#pragma once

#include "Topography/LocalMap.h"
#include "PathfindingRoute.h"
#include "PathingSpecs.h"
#include <vector>
#include <climits>

struct PathingNode {
	TileCoords tile;
	int distance;
	int priority;

	PathingNode(TileCoords tile = {-1,-1}, int dist = INT_MAX, int priority = INT_MAX) : tile(tile),
		distance(dist), priority(priority) {};

	bool operator < (const PathingNode& node) const {
		return priority < node.priority;
	}
	bool operator > (const PathingNode& node) const {
		return priority > node.priority;
	}
};

class TileCoordsHash {
public:
	size_t operator()(const TileCoords tile) const {
		return tile.x + tile.y * 256;
	}
};


typedef bool (LocalMap::*TraversibilityFunc)(TileCoords);

class Pathfinding {
private:
	static std::vector<TileCoords> getSurroundingTiles(TileCoords center);


	static void makeLineRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route);

	static void makeAStarRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route);

   static void calcRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route);

public:
   static void calcPath(PathingSpecs specs, LocalMap* map, PathingRoute& route);
};

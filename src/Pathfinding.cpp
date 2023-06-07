#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathingSpecs.h"
#include "Logs/DebugLogger.h"
#include "Topography/TileCoordinates.h"
#include <climits>
#include <functional>
#include <queue>
#include <unordered_map>
#include <string>


void Pathfinding::calcPath(PathingSpecs specs, LocalMap* map, PathingRoute& route) {
   if(!map->isInMapBounds(specs.start) || !map->isInMapBounds(specs.end)) {
      DebugLogger::log("calcPath() start or end tile is out of bounds");
      return;
   }

   TraversibilityFunc traversible;

   switch (specs.traversibility) {
   case TRAV_IGNORE_NONE:
      traversible = &LocalMap::isTraversibleAt;
      break;
   case TRAV_INCLUDE_UNSEEN_TILES:
      traversible = &LocalMap::isTraversibleAndSeen;
      break;
   case TRAV_IGNORE_ACTORS:
      traversible = &LocalMap::isPenetratableAt;
      break;
   }

   switch (specs.type) {
   case PATH_ROUTE:
      calcRoute(specs, map, traversible, route);
      break;
   case PATH_LINE:
      makeLineRoute(specs, map, traversible, route);
      break;
   }

   route.resetProgress();
}


void Pathfinding::calcRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route) {
   //TODO: try bresenham, then A* if failed
   makeLineRoute(specs, map, traversible, route);
   if (route.endTile() != specs.end) {
      makeAStarRoute(specs, map, traversible, route);
   }
}
   

void Pathfinding::makeLineRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route) {
	/*
	Based on the following article: https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
	And this: https://github.com/anushaihalapathirana/Bresenham-line-drawing-algorithm/blob/master/src/index.js
	*/

	route.clear();


   TileCoords startTile = specs.start;
   TileCoords endTile = specs.end;
   int maxLength = 500;
	int deltaX = abs(endTile.x - startTile.x);
	int deltaY = abs(endTile.y - startTile.y);

	int modifiedError = 0;

	int loopIncrement, secondaryIncrement;

   if (specs.type == PATH_LINE) {
      maxLength = specs.lineInfo.range;
   }

	if (deltaY <= deltaX) {

		int y = startTile.y;

		loopIncrement = startTile.x < endTile.x ? 1 : -1;
		secondaryIncrement = startTile.y < endTile.y ? 1 : -1;

		//one iteration outside to skip start tile
		if (2 * (modifiedError + deltaY) < deltaX) {
			modifiedError += deltaY;
		}
		else {
			y += secondaryIncrement;
			modifiedError += deltaY - deltaX;
		}

		for (int x = startTile.x+loopIncrement; x != endTile.x + loopIncrement; x += loopIncrement) {
         if (route.length() >= maxLength) {
            break;
         }
         if (TileCoords(x,y) == endTile) {
            route.addTile({x,y});
            break;
         }
			if ( !std::invoke(traversible, map, TileCoords(x,y)) ) {
            route.addTile({x,y});
				break;
			}
			route.addTile({ x,y });

			if (2 * (modifiedError + deltaY) < deltaX) {
				modifiedError += deltaY;
			}
			else {
				y += secondaryIncrement;
				modifiedError += deltaY - deltaX;
			}
		}

	}

	else {
		int x = startTile.x;

		loopIncrement = startTile.y < endTile.y ? 1 : -1;
		secondaryIncrement = startTile.x < endTile.x ? 1 : -1;

		//one iteration outside to skip first tile
		if (2 * modifiedError + deltaX < deltaY) {
			modifiedError += deltaX;
		}
		else {
			x += secondaryIncrement;
			modifiedError += deltaX - deltaY;
		}

		for (int y = startTile.y+loopIncrement; y != endTile.y + loopIncrement; y += loopIncrement) {
         if (route.length() >= maxLength) {
            break;
         }
         if (TileCoords(x,y) == endTile) {
            route.addTile({x,y});
            break;
         }
			if ( !std::invoke(traversible, map, TileCoords(x,y)) ) {
            route.addTile({x,y});
				break;
			}
			route.addTile({ x,y });

			if (2 * modifiedError + deltaX < deltaY) {
				modifiedError += deltaX;
			}
			else {
				x += secondaryIncrement;
				modifiedError += deltaX - deltaY;
			}
		}

	}
}

void Pathfinding::makeAStarRoute(PathingSpecs& specs, LocalMap* map, TraversibilityFunc traversible, PathingRoute& route) {
	/* Thanks to Amit Patel for his blogs on pathfinding */
	route.clear();

   TileCoords startTile = specs.start;
   TileCoords endTile = specs.end;

	std::priority_queue<PathingNode, std::vector<PathingNode>, std::greater<PathingNode>> frontier;
	std::unordered_map<TileCoords, PathingNode, TileCoordsHash> visited;
	std::unordered_map<TileCoords, TileCoords, TileCoordsHash> cameFrom;

	std::vector<TileCoords> surroundOffsets = { {1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1}, {1,0},{-1,0} };

	PathingNode current = PathingNode(endTile, 0, 0);
	cameFrom[endTile] = { -1,-1 };
	visited[endTile] = current;
	frontier.push(current);

	while (!frontier.empty()) {
		current = frontier.top();
		frontier.pop();

		if (current.tile == startTile) {
			break;
		}

		for (int i = 0; i < surroundOffsets.size(); i++) {
			TileCoords tile = current.tile + surroundOffsets[i];
			if (!map->isInMapBounds(tile) || (!std::invoke(traversible, map, tile) && tile != startTile)) {
				continue;
			}

			int nextDistance = (i<4) ? current.distance+141 : current.distance + 100;

			int nextPriority = nextDistance + std::max(abs(startTile.x - tile.x), abs(startTile.y - tile.y)) * 100;
			nextPriority += std::min(abs(startTile.x - tile.x), abs(startTile.y - tile.y)) * 40;

			if (visited.find(tile) == visited.end()) {
				PathingNode next = PathingNode(tile, nextDistance, nextPriority);

				cameFrom[tile] = current.tile;
				visited[tile] = next;
				frontier.push(next);

				continue;
			}

			PathingNode next = visited[tile];

			if (next.distance > nextDistance) {
				next = visited[tile];
				next.distance = nextDistance;
				next.priority = nextPriority;

				cameFrom[tile] = current.tile;
				visited[tile] = next;
				frontier.push(next);
			}
		}
	}

	if (current.tile != startTile) {
		return;
	}

	TileCoords tile = current.tile;
	TileCoords end = { -1,-1 };

	while (cameFrom[tile] != end) {
		tile = cameFrom[tile];
		route.addTile(tile);
	}
}


std::vector<TileCoords> Pathfinding::getSurroundingTiles(TileCoords center) {
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

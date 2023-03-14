#include "Algorithms/Pathfinding.h"
#include <functional>
#include <queue>
#include <unordered_map>
#include <string>


void Pathfinding::calcPlayerPathingRoute(TileCoords startTile, TileCoords endTile, LocalMap* map, PathingRoute* route) {
	MapDisplay* display = map->getMapDisplay();
	int endIndex = map->coordsToTileIndex(endTile);
	if (display->isVisible(endIndex)) {
		makeLineRoute(startTile, endTile, map, &LocalMap::isTraversibleAt, route);
	}
	else if (display->hasBeenSeen(endIndex)) {
		makeAStarRoute(startTile, endTile, map, *route);
	}
	else {
		route->clear();
		return;
	}
}

void Pathfinding::makeLineRoute(TileCoords startTile, TileCoords endTile, LocalMap* localMap, bool (LocalMap::*traversible)(TileCoords), PathingRoute* route) {
	/*
	Based on the following article: https://www.cs.helsinki.fi/group/goa/mallinnus/lines/bresenh.html
	And this: https://github.com/anushaihalapathirana/Bresenham-line-drawing-algorithm/blob/master/src/index.js
	*/

	route->clear();

	int deltaX = abs(endTile.x - startTile.x);
	int deltaY = abs(endTile.y - startTile.y);

	int modifiedError = 0;

	int loopIncrement, secondaryIncrement;

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
		int x = startTile.x;
		x += loopIncrement;

		for (x; x != endTile.x + loopIncrement; x += loopIncrement) {
			if ( !std::invoke(traversible, localMap, TileCoords(x,y)) ) {
				break;
			}
			route->addTile({ x,y });

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
		int y = startTile.y;
		y += loopIncrement;
		

		for (y; y != endTile.y + loopIncrement; y += loopIncrement) {
			if ( !std::invoke(traversible, localMap, TileCoords(x, y)) ) {
				break;
			}
			route->addTile({ x,y });

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

void Pathfinding::makeAStarRoute(TileCoords startTile, TileCoords endTile, LocalMap* map, PathingRoute& route) {
	/* Thanks to Amit Patel for his blogs on pathfinding */
	route.clear();

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
			if (!map->isInMapBounds(tile) || !map->hasBeenSeen(tile) || (tile != startTile && !map->isTraversibleAt(tile))) {
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

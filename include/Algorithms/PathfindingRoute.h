#pragma once

#include <vector>
#include "Topography/TileCoordinates.h"

class PathingRoute {
private:
	std::vector<TileCoords> route;
	int progress;

public:
	PathingRoute() : progress(0) {};

	void clear();
	void resetProgress();
	void addTile(TileCoords tile);
	TileCoords getNextTile();
	void incrementProgress();
	int size();
	bool hasNextTile();
	TileCoords endTile();
};

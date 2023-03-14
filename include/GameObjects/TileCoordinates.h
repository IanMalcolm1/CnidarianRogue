#pragma once

#include <stdint.h>


struct TileCoords {
	int16_t x, y;

	TileCoords(int x = -1, int y = -1) : x(x), y(y) {};

	bool operator == (const TileCoords coords) const {
		return (x == coords.x && y == coords.y);
	}

	bool operator != (const TileCoords coords) const {
		return (!(x == coords.x && y == coords.y));
	}

	TileCoords operator + (const TileCoords coords) const {
		return TileCoords(x + coords.x, y + coords.y);
	}
};

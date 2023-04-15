#pragma once


struct TileCoords {
	int x, y;

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

   bool isAdjacentTo(TileCoords coords) {
      if (x-coords.x <= 1 && x-coords.x >= -1 &&
            y-coords.y <= 1 && y-coords.y >= -1)
         return true;

      return false;
   }
};

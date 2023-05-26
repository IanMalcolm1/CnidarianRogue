#pragma once

#include "Adventure/Scene/Scene.h"
#include <random>

class TerrainGenerator {
private:
   std::mt19937 randGen;

public:
   TerrainGenerator();

	void rectangleRooms(Scene* scene, int numRectangles, int maxRectangleSideLength);
};

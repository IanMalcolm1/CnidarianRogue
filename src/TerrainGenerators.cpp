#include "Algorithms/TerrainGenerators.h"
#include <random>


TerrainGenerator::TerrainGenerator() {
   std::random_device seeder;
   randGen = std::mt19937(seeder());
}

void TerrainGenerator::rectangleRooms(Scene* scene, int numRectangles, int maxSideLength) {
	LocalMap* map = scene->getMap();

	int width = map->getWidth();
	int height = map->getHeight();

   std::uniform_int_distribution rectSizeDist(6, maxSideLength);
   std::uniform_int_distribution rectXDist(1, width-maxSideLength-1);
   std::uniform_int_distribution rectYDist(1, height-maxSideLength-1);
   std::uniform_int_distribution itemRollDist(0,3);

	MyColor white = MyColor(255, 255, 255);
	MyColor black = MyColor(0, 0, 0);

	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG, white, black);

	TileDisplay floorDisp = TileDisplay(ASYM_DOT, white, black);


	for (int i = 0; i < width * height; i++) {
		map->setTerrainAt(i, wallDisp, false, true);
	}

	int rectx, recty, rectWidth, rectHeight, currCenterX, currCenterY;
	int prevCenterX = -1, prevCenterY = -1;

	for (int i = 0; i < numRectangles; i++) {
		rectx = rectXDist(randGen);
		recty = rectXDist(randGen);

		rectWidth = rectSizeDist(randGen);
		rectHeight = rectSizeDist(randGen);

		for (int x = rectx; x < rectx + rectWidth; x++) {
			for (int y = recty; y < recty + rectHeight; y++) {
				map->setTerrainAt({x,y}, floorDisp, true, false);
			}
		}

		currCenterX = rectx + rectWidth / 2;
		currCenterY = recty + rectHeight / 2;

		if (prevCenterX < 0) {
			prevCenterX = currCenterX;
			prevCenterY = currCenterY;
			continue;
		}

		int sign = 1;
		int lineX;

		if (currCenterX < prevCenterX) {
			for (lineX = currCenterX; lineX <= prevCenterX; lineX++) {
				map->setTerrainAt({ lineX, currCenterY }, floorDisp, true, false);
			}
		}
		else {
			for (lineX = currCenterX; lineX >= prevCenterX; lineX--) {
				map->setTerrainAt({ lineX, currCenterY }, floorDisp, true, false);
			}
		}

		if (currCenterY < prevCenterY) {
			for (int lineY = currCenterY; lineY <= prevCenterY; lineY++) {
				map->setTerrainAt({ lineX, lineY }, floorDisp, true, false);
			}
		}
		else {
			for (int lineY = currCenterY; lineY >= prevCenterY; lineY--) {
				map->setTerrainAt({ lineX, lineY },	floorDisp, true, false);
			}
		}

		prevCenterX = currCenterX;
		prevCenterY = currCenterY;

      switch (itemRollDist(randGen)) {
         case 0:
            scene->getItemFactory()->makeIntelligenceMushroom({currCenterX, currCenterY});
            break;
         case 1:
            scene->getItemFactory()->makeStrengthFruit({currCenterX, currCenterY});
            break;
         case 2:
            scene->getItemFactory()->makeBasicSword({currCenterX, currCenterY});
            break;
         default:
            break;
      }
      
         
	}

	scene->setPlayerAt({ prevCenterX, prevCenterY });
	scene->getActorFactory()->makeEvilSmileyFace({prevCenterX-1, prevCenterY});
}

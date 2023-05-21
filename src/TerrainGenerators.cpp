#include "Algorithms/TerrainGenerators.h"
#include <random>

void TerrainGenerators::rectangleRooms(Scene* scene, int numRectangles, int maxSideLength) {
	LocalMap* map = scene->getMap();

	int width = map->getWidth();
	int height = map->getHeight();

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
		rectx = rand() % (width - maxSideLength) + 1;
		recty = rand() % (height - maxSideLength) + 1;

		rectWidth = rand() % (maxSideLength - 6) + 6;
		rectHeight = rand() % (maxSideLength - 6) + 6;

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

      int itemRoll = rand()%5;
      switch (itemRoll) {
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

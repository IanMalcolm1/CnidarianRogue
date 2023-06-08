#include "Algorithms/TerrainGenerator.h"
#include "Enums/AsciiSymbols.h"
#include "Topography/TerrainMap.h"


void TerrainGenerator::setSceneAndMap(Scene* scene) {
   this->scene = scene;
   map = scene->getMap();
   itemFactory = scene->getItemFactory();
   actorFactory = scene->getActorFactory();
   mapWidth = map->getWidth();
   mapHeight = map->getHeight();
   placeableTiles.clear();
}

void TerrainGenerator::rectangleRooms(Scene* scene, int numRectangles, int maxSideLength) {
   setSceneAndMap(scene);

   int wallNameId = map->addTerrainName("Wall");
   int floorNameId = map->addTerrainName("Floor");
   int stairsNameId = map->addTerrainName("Stairs Down");

   MyColor white = {255,255,255};
   MyColor black = {0,0,0};
	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG, white, black);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT, white, black);
	TileDisplay stairsDownDisp = TileDisplay(ASYM_LESS_THAN, white, black);

   TerrainTile wall = TerrainTile(TERRAIN_NORMAL, wallNameId, wallDisp, false, true);
   TerrainTile floor = TerrainTile(TERRAIN_NORMAL, floorNameId, floorDisp, true, false);
   TerrainTile stairsDown = TerrainTile(TERRAIN_DOWNSTAIRS, stairsNameId, stairsDownDisp, true, false);

   fillMap(wall);

   SDL_Rect rect;
	TileCoords currCenter;
   TileCoords prevCenter = {-1,-1};

	for (int i = 0; i < numRectangles; i++) {
      rect.x = randomizer.getRandomNumber(1, mapWidth-maxSideLength);
      rect.y = randomizer.getRandomNumber(1, mapHeight-maxSideLength);
      rect.w = randomizer.getRandomNumber(8, maxSideLength);
      rect.h = randomizer.getRandomNumber(8, maxSideLength);

		currCenter.x = rect.x + rect.w/2;
		currCenter.y = rect.y + rect.h/2;

      drawRectangle(rect, floor);

		if (prevCenter.x > -1) {
         drawRightAngleLine(currCenter, prevCenter, floor);
		}

      makeRandomItemAt(currCenter);

      prevCenter = currCenter;
	}

   int downStairsInd = randomizer.getRandomNumber(placeableTiles.size()-1);
   map->setTerrainAt(placeableTiles[downStairsInd], stairsDown);

	scene->setPlayerAt(currCenter);

   for (int i=0; i<4; i++) {
      TileCoords enemyLoc = placeableTiles[randomizer.getRandomNumber(placeableTiles.size()-1)];
      if (!map->thereIsAnActorAt(enemyLoc)) {
	      actorFactory->makeEvilSmileyFace(enemyLoc);
      }
   }
}

   
void TerrainGenerator::drawRectangle(SDL_Rect rect, TerrainTile& terrain) {
		for (int x = rect.x; x < rect.x+rect.w; x++) {
			for (int y = rect.y; y < rect.y+rect.h; y++) {
				map->setTerrainAt({x,y}, terrain);
            if (terrain.isTraversible) {
               placeableTiles.push_back({x,y});
            }
			}
		}
}

void TerrainGenerator::fillMap(TerrainTile& terrain) {
   for (int x = 0; x<mapWidth; x++) {
      for (int y = 0; y<mapHeight; y++) {
         map->setTerrainAt({x,y}, terrain);
      }
   }
}

void TerrainGenerator::drawRightAngleLine(TileCoords start, TileCoords end, TerrainTile& terrain) {
   int linex;
   if (start.x < end.x) {
      for (linex = start.x; linex <= end.x; linex++) {
         map->setTerrainAt({ linex, start.y }, terrain);
      }
   }
   else {
      for (linex = start.x; linex >= end.x; linex--) {
         map->setTerrainAt({ linex, start.y }, terrain);
      }
   }

   if (start.y < end.y) {
      for (int liney = start.y; liney <= end.y; liney++) {
         map->setTerrainAt({ linex, liney }, terrain);
      }
   }
   else {
      for (int liney = start.y; liney >= end.y; liney--) {
         map->setTerrainAt({ linex, liney },	terrain);
      }
   }
}


void TerrainGenerator::makeRandomItemAt(TileCoords tile) {
   switch (randomizer.getRandomNumber(5)) {
      case 0:
         itemFactory->makeIntelligenceMushroom(tile);
         break;
      case 1:
         itemFactory->makeStrengthFruit(tile);
         break;
      case 2:
         itemFactory->makeBasicSword(tile);
         break;
      case 3:
         itemFactory->makeForceWand(tile);
         break;
      case 4:
         itemFactory->makeGambeson(tile);
         break;
      default:
         break;
   }
}

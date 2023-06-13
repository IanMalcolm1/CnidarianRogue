#include "Algorithms/TerrainGenerator.h"
#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathingSpecs.h"
#include "Enums/AsciiSymbols.h"
#include "GraphicsThings/ColorPalette.h"
#include "SDL_rect.h"
#include "Topography/TerrainMap.h"
#include <functional>



void TerrainGenerator::setSceneAndMap(Scene* scene) {
   this->scene = scene;
   map = scene->getMap();
   itemFactory = scene->getItemFactory();
   actorFactory = scene->getActorFactory();
   mapWidth = map->getWidth();
   mapHeight = map->getHeight();
   placeableTiles.clear();
}

void TerrainGenerator::floor1(Scene* scene) {
   setSceneAndMap(scene);

   ColorPalette floorPalette;
   floorPalette.addColor(158,158,158);
   floorPalette.addColor(164, 164, 164);
   floorPalette.addColor(171, 159, 137);

   int wallNameId = map->addTerrainName("Wall");
   int floorNameId = map->addTerrainName("Floor");
   int stairsNameId = map->addTerrainName("Stairs Down");
   int altarNameId = map->addTerrainName("Sacrificial Altar");

   MyColor white = {255,255,255};
   MyColor black = {0,0,0};
	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG, white, black);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT, white, black);
	TileDisplay stairsDownDisp = TileDisplay(ASYM_LESS_THAN, white, black);
	TileDisplay altarDisp = TileDisplay(ASYM_PYRAMID, MyColor(255,96,96), black);

   TerrainTile wallTile = TerrainTile(TERRAIN_NORMAL, wallNameId, wallDisp, false, true);
   TerrainTile floorTile = TerrainTile(TERRAIN_NORMAL, floorNameId, floorDisp, true, false);
   TerrainTile altar = TerrainTile(TERRAIN_NORMAL, altarNameId, altarDisp, false, false);
   TerrainTile stairsDown = TerrainTile(TERRAIN_DOWNSTAIRS, stairsNameId, stairsDownDisp, true, false);

   GeneratorTile floor = GeneratorTile(floorTile, floorPalette);
   GeneratorTile wall = GeneratorTile(wallTile, floorPalette);


   fillMap(wall);
   auto rooms = makeRectangleRooms(10, 20, floor);

   
   //player
   TileCoords playertile;
   int playerRoomIndex;
   SDL_Rect playerRoom;
   while (true) {
      playerRoomIndex = randomizer.getRandomNumber(rooms.size()-1);
      playerRoom = rooms[playerRoomIndex];
      if (playerRoom.x < mapWidth/4 || playerRoom.x > mapWidth/2) {
         if (playerRoom.y < mapHeight/4 || playerRoom.y > mapHeight/2) {
            break;
         }
      }
   }
   playertile.x = playerRoom.x+playerRoom.w/2;
   playertile.y = playerRoom.y+playerRoom.h/2;
   scene->setPlayerAt(playertile);


   //boss
   TileCoords bosstile;
   int bossRoomIndex;
   SDL_Rect bossRoom;
   for (int i=0; i<rooms.size(); i++) {
      if (i==playerRoomIndex) {
         continue;
      }

      bossRoomIndex = i;
      bossRoom = rooms[bossRoomIndex];
      
      bosstile.x = bossRoom.x+bossRoom.w/2;
      bosstile.y = bossRoom.y+bossRoom.h/2;

      if (distanceBetween(bosstile, playertile) > (mapWidth*3)/4) {
         break;
      }

      if (i == rooms.size()-1) {
         floor1(scene);
         return;
      }
   }

   actorFactory->makeArmoredCultist(bosstile);
   map->setTerrainAt(bosstile, stairsDown);
   map->setTerrainAt({bosstile.x+1, bosstile.y}, altar);
   map->setTerrainAt({bosstile.x-1, bosstile.y}, altar);
   map->setTerrainAt({bosstile.x, bosstile.y+1}, altar);
   map->setTerrainAt({bosstile.x, bosstile.y-1}, altar);
   spawnCultists(bossRoom);


   //misc cultists
   for (int i=0; i<rooms.size(); i++) {
      if (i==playerRoomIndex || i==bossRoomIndex) {
         continue;
      }
      spawnCultists(rooms[i]);
   }
}


void TerrainGenerator::floor2(Scene* scene) {
   setSceneAndMap(scene);

   ColorPalette caveFloorPalette;
   caveFloorPalette.addColor(145, 124, 89);
   caveFloorPalette.addColor(131, 151, 129);
   caveFloorPalette.addColor(172, 132, 70);

   ColorPalette caveWallPalette;
   caveWallPalette.addColor(84, 128, 77);
   caveWallPalette.addColor( 115, 132, 113 );
   caveWallPalette.addColor( 84, 110, 80 );

   int wallNameId = map->addTerrainName("Cave Wall");
   int floorNameId = map->addTerrainName("Ground");
   int stairsNameId = map->addTerrainName("Stairs Down");

   MyColor white = {255,255,255};
   MyColor black = {0,0,0};
	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG, white, black);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT, white, black);
	TileDisplay stairsDownDisp = TileDisplay(ASYM_LESS_THAN, white, black);

   TerrainTile wallTile = TerrainTile(TERRAIN_NORMAL, wallNameId, wallDisp, false, true);
   TerrainTile floorTile = TerrainTile(TERRAIN_NORMAL, floorNameId, floorDisp, true, false);
   TerrainTile stairsDown = TerrainTile(TERRAIN_DOWNSTAIRS, stairsNameId, stairsDownDisp, true, false);

   GeneratorTile wall = GeneratorTile(wallTile, caveWallPalette);
   GeneratorTile floor = GeneratorTile(floorTile, caveFloorPalette);

   fillMap(wall);

   auto rooms = makeRectangleRooms(10, 20, floor);
   TileCoords playertile;
   playertile.x = rooms[0].x+rooms[0].w/2;
   playertile.y = rooms[0].y+rooms[0].h/2;
   scene->setPlayerAt(playertile);
}



void TerrainGenerator::floor3(Scene* scene) {
   floor1(scene);
}


std::vector<SDL_Rect> TerrainGenerator::makeRectangleRooms(int numRectangles, int maxSideLength, GeneratorTile& terrain) {
   std::vector<SDL_Rect> rooms;
   SDL_Rect rect;
	TileCoords currCenter;
   TileCoords prevCenter = {-1,-1};

	for (int i = 0; i < numRectangles; i++) {
      rect.x = randomizer.getRandomNumber(1, mapWidth-maxSideLength-1);
      rect.y = randomizer.getRandomNumber(1, mapHeight-maxSideLength-1);
      rect.w = randomizer.getRandomNumber(8, maxSideLength);
      rect.h = randomizer.getRandomNumber(8, maxSideLength);

		currCenter.x = rect.x + rect.w/2;
		currCenter.y = rect.y + rect.h/2;

      bool needRedo = false;
      for (SDL_Rect room : rooms) {
         if (SDL_HasIntersection(&rect, &room)) {
            needRedo = true;
         }
      }
      if (needRedo) {
         i--;
         continue;
      }

      drawRectangle(rect, terrain);
      rooms.push_back(rect);

		if (prevCenter.x > -1) {
         drawRightAngleLine(currCenter, prevCenter, terrain);
		}

      prevCenter = currCenter;
	}

   return rooms;
}

   
void TerrainGenerator::drawRectangle(SDL_Rect rect, GeneratorTile& terrain) {
   for (int x = rect.x; x < rect.x+rect.w; x++) {
      for (int y = rect.y; y < rect.y+rect.h; y++) {
         placeTerrain({x,y}, terrain);
         if (terrain.tile.isTraversible) {
            placeableTiles.push_back({x,y});
         }
      }
   }
}


std::vector<TileCoords> TerrainGenerator::carveDrunkard(GeneratorTile& terrain, int lifespan) {
   TileCoords drunkard;
}


void TerrainGenerator::spawnCultists(SDL_Rect room) {
   int numWarriors = randomizer.getRandomNumber(2);
   int numPreachers = randomizer.getRandomNumber(1);

   for (int i=0; i<numWarriors; i++) {
      TileCoords tile;
      do {
         tile.x = room.x + randomizer.getRandomNumber(room.w-1);
         tile.y = room.y + randomizer.getRandomNumber(room.h-1);
      } while (!map->isTraversibleAt(tile));

      actorFactory->makeCultistWarrior(tile);
   }

   for (int i=0; i<numPreachers; i++) {
      TileCoords tile;
      do {
         tile.x = room.x + randomizer.getRandomNumber(room.w-1);
         tile.y = room.y + randomizer.getRandomNumber(room.h-1);
      } while (!map->isTraversibleAt(tile));

      actorFactory->makeWandCultist(tile);
   }
}


void TerrainGenerator::fillMap(GeneratorTile& terrain) {
   for (int x = 0; x<mapWidth; x++) {
      for (int y = 0; y<mapHeight; y++) {
         placeTerrain({x,y}, terrain);
      }
   }
}

void TerrainGenerator::drawRightAngleLine(TileCoords start, TileCoords end, GeneratorTile& terrain) {
   int linex;
   if (start.x < end.x) {
      for (linex = start.x; linex <= end.x; linex++) {
         placeTerrain({linex,start.y}, terrain);
      }
   }
   else {
      for (linex = start.x; linex >= end.x; linex--) {
         placeTerrain({linex,start.y}, terrain);
      }
   }

   if (start.y < end.y) {
      for (int liney = start.y; liney <= end.y; liney++) {
         placeTerrain({linex,liney}, terrain);
      }
   }
   else {
      for (int liney = start.y; liney >= end.y; liney--) {
         placeTerrain({linex,liney}, terrain);
      }
   }
}

void TerrainGenerator::placeTerrain(TileCoords location, GeneratorTile& terrain) {
   terrain.tile.display.symbolColor = terrain.palette.getRandomColor(&randomizer);
   map->setTerrainAt(location, terrain.tile);
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


int TerrainGenerator::distanceBetween(TileCoords tile1, TileCoords tile2) {
   PathingSpecs specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_ACTORS);
   specs.start = tile1;
   specs.end = tile2;
   Pathfinding::calcPath(specs, map, distanceTester);

   return distanceTester.length();
}

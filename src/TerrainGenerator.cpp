#include "Algorithms/TerrainGenerator.h"
#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathingSpecs.h"
#include "Enums/AsciiSymbols.h"
#include "GraphicsThings/ColorPalette.h"
#include "Logs/DebugLogger.h"
#include "SDL_rect.h"
#include "Topography/TerrainMap.h"
#include "Topography/TileCoordinates.h"
#include <climits>
#include <functional>
#include <string>
#include <unordered_set>



void TerrainGenerator::setSceneAndMap(Scene* scene) {
   this->scene = scene;
   map = scene->getMap();
   itemFactory = scene->getItemFactory();
   actorFactory = scene->getActorFactory();
   mapWidth = map->getWidth();
   mapHeight = map->getHeight();
   placeableTiles.clear();
}


void TerrainGenerator::makeFloor(int floorNum, Scene* scene) {
   setSceneAndMap(scene);

   switch (floorNum) {
      case 0:
         floor0(scene);
         break;
      case 1:
         floor1(scene);
         break;
      case 2:
         floor2(scene);
         break;
      default:
         DebugLogger::log("Invalid floor number");
   }
}

void TerrainGenerator::floor0(Scene* scene) {
   ColorPalette floorPalette;
   floorPalette.addColor(158,158,158);
   floorPalette.addColor(164, 164, 164);
   floorPalette.addColor(171, 159, 137);

   int wallNameId = map->addTerrainName("Wall");
   int floorNameId = map->addTerrainName("Floor");
   int stairsNameId = map->addTerrainName("Damp Tunnel");
   int altarNameId = map->addTerrainName("Feeding Altar");

	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT);
	TileDisplay stairsDownDisp = TileDisplay(ASYM_LESS_THAN);
	TileDisplay altarDisp = TileDisplay(ASYM_PYRAMID, Color(255,96,96));

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
         floor0(scene);
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


void TerrainGenerator::floor1(Scene* scene) {
   ColorPalette caveFloorPalette;
   caveFloorPalette.addColor(145, 124, 89);
   caveFloorPalette.addColor(131, 151, 129);
   caveFloorPalette.addColor(172, 132, 70);

   ColorPalette caveWallPalette;
   caveWallPalette.addColor(84, 128, 77);
   caveWallPalette.addColor(115, 132, 113);
   caveWallPalette.addColor(84, 110, 80);

   ColorPalette mushroomPalette;
   mushroomPalette.addColor(177, 150, 196);
   mushroomPalette.addColor(182, 164, 195);

   int wallNameId = map->addTerrainName("Cave Wall");
   int floorNameId = map->addTerrainName("Ground");
   int stairsNameId = map->addTerrainName("Small Opening");
   int mushroomNameId = map->addTerrainName("Mushroom Patch");
   int bushNameId = map->addTerrainName("Cave Bush");

	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT);
	TileDisplay stairsDownDisp = TileDisplay(ASYM_LESS_THAN);
	TileDisplay mushroomDisp = TileDisplay(ASYM_SPARSE_DOTS);
	TileDisplay bushDisp = TileDisplay(ASYM_AE, Color(226, 166, 55));

   TerrainTile wallTile = TerrainTile(TERRAIN_NORMAL, wallNameId, wallDisp, false, true);
   TerrainTile floorTile = TerrainTile(TERRAIN_NORMAL, floorNameId, floorDisp, true, false);
   TerrainTile stairsDown = TerrainTile(TERRAIN_DOWNSTAIRS, stairsNameId, stairsDownDisp, true, false);
   TerrainTile mushroomTile = TerrainTile(TERRAIN_NORMAL, mushroomNameId, mushroomDisp, true, false);
   TerrainTile bush = TerrainTile(TERRAIN_NORMAL, bushNameId, bushDisp, true, false);

   GeneratorTile wall = GeneratorTile(wallTile, caveWallPalette);
   GeneratorTile floor = GeneratorTile(floorTile, caveFloorPalette);
   GeneratorTile mushrooms = GeneratorTile(mushroomTile, mushroomPalette);

   fillMap(wall);

   auto rooms = makeDrunkardRooms(floor, Fraction(2,5), 100);
   rooms = cullRooms(rooms, wall);
   populatePlaceableTiles(rooms);

   TileCoords playerTile = rooms[0][0];
   TileCoords bossTile;

   for (int i=0; i<rooms.size(); i++) {
      bossTile = placeableTiles[randomizer.getRandomNumber(placeableTiles.size()-1)];

      if (distanceBetween(bossTile, playerTile) > (mapWidth*3)/4) {
         break;
      }

      if (i == rooms.size()-1) {
         floor1(scene);
         return;
      }
   }
   actorFactory->makeCultistIdol(bossTile);
   map->setTerrainAt(bossTile, stairsDown);

   for (int i=0; i<3; i++) {
      TileCoords loc = placeableTiles[randomizer.getRandomNumber(placeableTiles.size()-1)];
      map->setTerrainAt(loc, bush);
      itemFactory->makeStrengthFruit(loc);
   }

   for (int i=0; i<2; i++) {
      TileCoords loc = placeableTiles[randomizer.getRandomNumber(placeableTiles.size()-1)];
      itemFactory->makeIntelligenceMushroom(loc);
      carveDrunkard(mushrooms, loc, 2);
   }

   for (auto room : rooms) {
      spawnCaveWildlife(room);
   }

   scene->setPlayerAt(playerTile);
}



void TerrainGenerator::floor2(Scene* scene) {
   ColorPalette caveFloorPalette;
   caveFloorPalette.addColor(145, 124, 89);
   caveFloorPalette.addColor(131, 151, 129);
   caveFloorPalette.addColor(172, 132, 70);

   ColorPalette caveWallPalette;
   caveWallPalette.addColor(84, 128, 77);
   caveWallPalette.addColor(115, 132, 113);
   caveWallPalette.addColor(84, 110, 80);

   int wallNameId = map->addTerrainName("Cave Wall");
   int floorNameId = map->addTerrainName("Ground");

	TileDisplay wallDisp = TileDisplay(ASYM_HASHTAG);
	TileDisplay floorDisp = TileDisplay(ASYM_DOT);

   TerrainTile wallTile = TerrainTile(TERRAIN_NORMAL, wallNameId, wallDisp, false, true);
   TerrainTile floorTile = TerrainTile(TERRAIN_NORMAL, floorNameId, floorDisp, true, false);

   GeneratorTile wall = GeneratorTile(wallTile, caveWallPalette);
   GeneratorTile floor = GeneratorTile(floorTile, caveFloorPalette);

   fillMap(wall);

   TileCoords bossTile = TileCoords(mapWidth/2, mapHeight/2);
   TileVector room = carveDrunkard(floor, bossTile, 1000);

   actorFactory->makeHydra(bossTile);

   scene->setPlayerAt(room.back());
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


TileVector TerrainGenerator::carveDrunkard(GeneratorTile& terrain, TileCoords startTile, int lifespan) {
   TileCoords drunkard = startTile;
   placeTerrain(drunkard, terrain);
   TileVector roomTiles;
   roomTiles.push_back(drunkard);

   for (int i=0; i<lifespan; i++) {
      TileCoords prevTile = drunkard;

      switch (randomizer.getRandomNumber(3)) {
      case 0:
         drunkard.x++;
         break;
      case 1:
         drunkard.y++;
         break;
      case 2:
         drunkard.x--;
         break;
      case 3:
         drunkard.y--;
         break;
      }

      if (drunkard.y < 1 || drunkard.y >= mapHeight-1 || drunkard.x < 1 || drunkard.x >= mapWidth-1) {
         drunkard = prevTile;
         continue;
      }

      if (map->getTerrainAt(drunkard) != terrain.tile) {
         placeTerrain(drunkard, terrain);
         roomTiles.push_back(drunkard);
      }
   }

   return roomTiles;
}


std::vector<TileVector> TerrainGenerator::makeDrunkardRooms(GeneratorTile& terrain, Fraction fraction, int drunkLifespan) {
   std::vector<TileVector> rooms;
   int spaceDesired = fraction.multiplyInt(mapWidth*mapHeight);

   while(calcSize(rooms) < spaceDesired) {
      rooms.push_back(carveDrunkard(terrain, getRandomTile(10), 100));
   }

   return rooms;
}


void TerrainGenerator::spawnCultists(SDL_Rect room) {
   int numWarriors = randomizer.getRandomNumber(2);
   int numPreachers = randomizer.flipCoin();
   int numDogs = randomizer.getRandomNumber(3)/3;

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

   for (int i=0; i<numWarriors; i++) {
      TileCoords tile;
      do {
         tile.x = room.x + randomizer.getRandomNumber(room.w-1);
         tile.y = room.y + randomizer.getRandomNumber(room.h-1);
      } while (!map->isTraversibleAt(tile));

      actorFactory->makeBadDog(tile);
   }
}


void TerrainGenerator::spawnCaveWildlife(TileVector room) {
   int numSnakes = randomizer.getRandomNumber(7)/7;


   for (int i=0; i<numSnakes; i++) {
      TileCoords tile;
      do {
         tile = room[randomizer.getRandomNumber(room.size()-1)];
      } while (!map->isTraversibleAt(tile));

      actorFactory->makeCnidas(tile);
   }
}


void TerrainGenerator::fillMap(GeneratorTile& terrain) {
   for (int x = 0; x<mapWidth; x++) {
      for (int y = 0; y<mapHeight; y++) {
         placeTerrain({x,y}, terrain);
      }
   }
}

void TerrainGenerator::populatePlaceableTiles(std::vector<TileVector>& rooms) {
   for (auto room : rooms) {
      for (auto tile : room) {
         placeableTiles.push_back(tile);
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


int TerrainGenerator::distanceBetween(TileCoords start, TileCoords end) {
   PathingSpecs specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_ACTORS);
   specs.start = start;
   specs.end = end;
   Pathfinding::calcPath(specs, map, distanceTester);

   return distanceTester.length();
}

bool TerrainGenerator::thereIsAPathBetween(TileCoords start, TileCoords end) {
   if (start==end) {
      return true;
   }

   PathingSpecs specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_ACTORS);
   specs.start = start;
   specs.end = end;
   Pathfinding::calcPath(specs, map, distanceTester);

   return distanceTester.length() > 0;
}


TileCoords TerrainGenerator::getRandomTile(int margin) {
   return TileCoords(randomizer.getRandomNumber(margin, mapWidth-1-margin), randomizer.getRandomNumber(margin, mapHeight-1-margin));
}


std::vector<TileVector> TerrainGenerator::cullRooms(std::vector<TileVector>& rooms, GeneratorTile& fillTerrain) {
   std::vector<std::vector<TileVector>> roomGroups;
   std::vector<int> visitedRooms;
   int index;

   for (int i=0; i<rooms.size(); i++) {
      //if index is in visited rooms, skip it
      if (std::find(visitedRooms.begin(), visitedRooms.end(), i) != visitedRooms.end()) {
         continue;
      }

      visitedRooms.push_back(i); //unnecesssary?

      std::vector<TileVector> roomGroup;
      roomGroup.push_back(rooms[i]);
      roomGroups.push_back(roomGroup);

      int j=i+1;
      for (; j<rooms.size(); j++) {
         if (std::find(visitedRooms.begin(), visitedRooms.end(), j) != visitedRooms.end()) {
            continue;
         }

         if (thereIsAPathBetween(rooms[i][0], rooms[j][0])) {
            roomGroups.back().push_back(rooms[j]);
            visitedRooms.push_back(j);
         }
      }
   }

   int largestGroup = 0;
   int largestGroupSize = calcSize(roomGroups[0]);

   for (int i=1; i<roomGroups.size(); i++) {
      int iSize = calcSize(roomGroups[i]);
      if (iSize > largestGroupSize) {
         largestGroup = i;
         largestGroupSize = iSize;
      }
   }

   for (int i=0; i<roomGroups.size(); i++) {
      if (i==largestGroup) {
         continue;
      }
      fillRooms(roomGroups[i], fillTerrain);
   }

   return roomGroups[largestGroup];
}

int TerrainGenerator::calcSize(std::vector<TileVector>& rooms) {
   std::unordered_set<TileCoords, TileCoords::HashFunction> visitedTiles;
   int size = 0;

   for (auto room : rooms) {
      for (auto tile : room) {
         if (visitedTiles.find(tile)==visitedTiles.end()) {
            visitedTiles.insert(tile);
            size++;
         }
      }
   }

   return size;
}


void TerrainGenerator::fillRooms(std::vector<TileVector>& rooms, GeneratorTile& terrain) {
   for (auto room : rooms) {
      fillRoom(room, terrain);
   }
}

void TerrainGenerator::fillRoom(TileVector& room, GeneratorTile& terrain) {
   for (auto tile : room) {
      placeTerrain(tile, terrain);
   }
}

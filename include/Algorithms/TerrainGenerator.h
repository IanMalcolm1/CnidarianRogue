#pragma once

#include "Adventure/Scene/Scene.h"
#include "GraphicsThings/ColorPalette.h"



class TerrainGenerator {
   typedef void (TerrainGenerator::*SpawningFunction)(std::vector<TileCoords>&);

private:
   Scene* scene;
   LocalMap* map;
   ItemFactory* itemFactory;
   ActorFactory* actorFactory;

   int mapWidth, mapHeight;

   Randomizer randomizer;
   PathingRoute distanceTester;

   std::vector<TileCoords> placeableTiles;

   void setSceneAndMap(Scene* scene);

   void fillMap(TerrainTile& terrain, ColorPalette& palette);
   void drawRectangle(SDL_Rect rect, TerrainTile& terrain, ColorPalette& palette);
   void drawRightAngleLine(TileCoords start, TileCoords end, TerrainTile& terrain, ColorPalette& palette);

   std::vector<SDL_Rect> makeRectangleRooms(int numRectangles, int maxSideLength, TerrainTile& terrain, ColorPalette& palette);

   void placePaletteTile(TileCoords location, TerrainTile& terrain, ColorPalette& palette);

   void makeRandomItemAt(TileCoords tile);
   void spawnCultists(SDL_Rect room);

   int distanceBetween(TileCoords tile1, TileCoords tile2);


public:
   TerrainGenerator() : scene(nullptr), map(nullptr), randomizer() {};

   //Catacombs. Best for scene of size 96x96.
	void floor1(Scene* scene);

   //Caves. Best for scene of size 128,128.
	void floor2(Scene* scene);

   //Boss floor. Best for scene of size 32,32.
   void floor3(Scene* scene);
};

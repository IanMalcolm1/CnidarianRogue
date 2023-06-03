#pragma once

#include "Adventure/Scene/Scene.h"

class TerrainGenerator {
private:
   Scene* scene;
   LocalMap* map;
   ItemFactory* itemFactory;
   ActorFactory* actorFactory;

   int mapWidth, mapHeight;

   Randomizer randomizer;

   std::vector<TileCoords> traversibleTiles;

   void setSceneAndMap(Scene* scene);
   void fillMap(TerrainTile& terrain);
   void drawRectangle(SDL_Rect rect, TerrainTile& terrain);
   void drawRightAngleLine(TileCoords start, TileCoords end, TerrainTile& terrain);

   void makeRandomItemAt(TileCoords tile);

public:
   TerrainGenerator() : scene(nullptr), map(nullptr), randomizer() {};

	void rectangleRooms(Scene* scene, int numRectangles, int maxRectangleSideLength);
};

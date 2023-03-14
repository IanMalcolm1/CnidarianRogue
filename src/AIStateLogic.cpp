#include "Scene/Scene.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include <random>
#include <functional>


int Scene::performAction(Actor* actor) {
	AIStateID actorState = actor->getState();

	FoV::calcActorFoV(&map, actor);


	switch (actorState) {
	
	}

	return testerLogic(actor); //temporary
}

int Scene::testerLogic(Actor* actor) {
	PathingRoute* currentRoute = actor->getCurrentRoute();

	if (currentRoute->hasNextTile()) {
		TileCoords newTile = currentRoute->getNextTile();
		if (map.isTraversibleAt(newTile)) {
			moveActor(actor, newTile);
			currentRoute->incrementProgress();
			return FULL_TURN_TIME;
		}
	}

	if (rand() % 50 > 2) {
		return FULL_TURN_TIME;
	}

	std::vector<TileCoords>* visibleTiles = actor->getVisibleTiles();
	
	int newTileIndex;
	TileCoords newLocation;

	do {
		newTileIndex = rand() % visibleTiles->size();
		newLocation = visibleTiles->at(newTileIndex);
	} while (!map.isTraversibleAt(newLocation));

	Pathfinding::makeLineRoute(actor->getLocation(), visibleTiles->at(newTileIndex), &map, &LocalMap::isTraversibleAt, actor->getCurrentRoute());

	return actor->getStats()->baseMoveSpeed;
}

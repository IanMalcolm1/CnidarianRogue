#include "Scene/ActorManager.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Entities/ActorFactory.h"
#include "Scene/TurnQueue.h"
#include <cwchar>
#include <random>



void ActorManager::runActorTurns() {
	ActorEntity* currentActor = turnQueue.pop();
	while (currentActor != nullptr && !currentActor->isPlayer) {
		int timeTaken = runAction(currentActor);
		turnQueue.insert(currentActor, timeTaken);

		currentActor = turnQueue.pop();
	}

	map->flagNeedToUpdateDisplay();
}


int ActorManager::runAction(ActorEntity* actor) {
	AiStateId actorState = actor->getState();

	FoV::calcActorFoV(map, actor);

   return wander(actor);

   /*
    * switch statement for once add more possbilities than just wandering
	switch (actorState) {
      case AISTATE_WANDERING:
         return wander(actor);
      default:
         return actor->getStats()->baseMoveSpeed;
	}
*/
}


void ActorManager::destroyActor(ActorEntity* actor) {
	map->setActorAt(actor->location, nullptr);

	turnQueue.remove(actor);

   actorColiseum.deleteEntity(actor->getId());
}

void ActorManager::moveActor(ActorEntity* actor, TileCoords newLocation) {
   map->setActorAt(actor->location, nullptr);
   actor->location = newLocation;
   map->setActorAt(newLocation, actor);
}



int ActorManager::wander(ActorEntity* actor) {
	PathingRoute* currentRoute = actor->getCurrentRoute();

	if (currentRoute->hasNextTile()) {
		TileCoords newTile = currentRoute->getNextTile();
		if (map->isTraversibleAt(newTile)) {
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
	} while (!map->isTraversibleAt(newLocation));

	Pathfinding::makeLineRoute(actor->location, visibleTiles->at(newTileIndex), map, &LocalMap::isTraversibleAt, actor->getCurrentRoute());

	return actor->stats.baseMoveSpeed;
}


ActorFactory ActorManager::makeFactory() {
   return ActorFactory(&actorColiseum, &turnQueue, map);
}

TurnQueue* ActorManager::getTurnQueue() {
   return &turnQueue;
}

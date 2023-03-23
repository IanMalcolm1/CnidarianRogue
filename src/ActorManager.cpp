#include "Scene/ActorManager.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "GameObjects/AI.h"
#include "GameObjects/Actor.h"
#include "Scene/ActorPool.h"
#include "Scene/TurnQueue.h"
#include <cwchar>
#include <random>



void ActorManager::runActorTurns() {
	Actor* currentActor = turnQueue->pop();
	while (currentActor != nullptr && !currentActor->isPlayer()) {
		int timeTaken = runAction(currentActor);
		turnQueue->insert(currentActor, timeTaken);

		currentActor = turnQueue->pop();
	}

	map->flagNeedToUpdateDisplay();
}


int ActorManager::runAction(Actor* actor) {
	AIStateID actorState = actor->getState();

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


void ActorManager::createActorAt(TileCoords location) {
	Actor newActor = Actor();

	newActor.setLocation(location);

	Actor* newActorPointer = actorPool.insert(newActor);

	map->setActorAt(location, newActorPointer);
	turnQueue->insert(newActorPointer, 0);
}

void ActorManager::destroyActor(Actor* actor) {
	map->setActorAt(actor->getLocation(), nullptr);

	turnQueue->remove(actor);

	actorPool.kill(actor);
}

void ActorManager::moveActor(Actor* actor, TileCoords newLocation) {
   map->setActorAt(actor->getLocation(), nullptr);
   actor->setLocation(newLocation);
   map->setActorAt(newLocation, actor);
}



int ActorManager::wander(Actor* actor) {
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

	Pathfinding::makeLineRoute(actor->getLocation(), visibleTiles->at(newTileIndex), map, &LocalMap::isTraversibleAt, actor->getCurrentRoute());

	return actor->getStats()->baseMoveSpeed;
}

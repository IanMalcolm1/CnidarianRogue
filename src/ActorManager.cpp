#include "Scene/ActorManager.h"
#include "Entities/AI.h"
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
	FoV::calcActorFoV(map, actor);

   if (actor->getState() < AISTATE_ATTACKING) {
      for (auto location : (*actor->getVisibleActorLocations())) {
         if (actor->isHostileTo(map->getActorAt(location))) {
            actor->setState(AISTATE_ATTACKING);
         }
      }
   }

   else if (actor->getState() > AISTATE_ATTACKING) {
      if (actor->getVisibleActorLocations()->empty()) {
         actor->setState(AISTATE_IDLE);
      }
   }

	switch (actor->getState()) {
      case AISTATE_WANDERING:
         return wander(actor);
      case AISTATE_APPROACH_AND_WHACK:
         return approachAndWhack(actor);
      default:
         return actor->stats.baseMoveSpeed;
	}
}


void ActorManager::destroyActor(ActorEntity* actor) {
	map->setActorAt(actor->location, nullptr);
	turnQueue.remove(actor);

   for (auto item : (*actor->getItems())) {
      map->addItemAt(actor->location, item);
   }

   for (int i=0; i<actorColiseum.getDirtySlots(); i++) {
      if (actorColiseum.getEntity(i)->isTargetting(actor)) {
         actorColiseum.getEntity(i)->setTarget(NULL);
      }
   }

   actorColiseum.deleteEntity(actor->getId());
}

void ActorManager::moveActor(ActorEntity* actor, TileCoords newLocation) {
   map->setActorAt(actor->location, nullptr);
   actor->location = newLocation;
   map->setActorAt(newLocation, actor);
}


void ActorManager::doAttack(ActorEntity* attacker, ActorEntity* defender) {
   int damage = attacker->defaultAttack.damage1.constant;

   for (int i=0; i<attacker->defaultAttack.damage1.dice; i++) {
      damage += rand()%6+1;
   }

   defender->stats.health -= damage;

   if (defender->stats.health <= 0)
      destroyActor(defender);
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



int ActorManager::approachAndWhack(ActorEntity* actor) {
   

}


ActorFactory ActorManager::makeFactory() {
   return ActorFactory(&actorColiseum, &turnQueue, map);
}

TurnQueue* ActorManager::getTurnQueue() {
   return &turnQueue;
}

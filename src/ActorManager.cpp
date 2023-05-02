#include "Adventure/Scene/ActorManager.h"
#include "Entities/AI.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Entities/ActorFactory.h"
#include "Adventure/Scene/TurnQueue.h"
#include "EventListener/Listener.h"
#include <cwchar>
#include <random>
#include <string>


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

   actor->checkForHostiles();

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

   if (actor->isPlayer) {
      notifyListeners(EVENT_PLAYERDED);
      turnQueue.insert(actor, 0);
      return;
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
   int constant = attacker->defaultAttack.damage1.constant;
   int diceRoll = 0;
   for (int i=0; i<attacker->defaultAttack.damage1.dice; i++) {
      diceRoll += rand()%6+1;
   }

   
   std::string message = attacker->description.name;
   message.append(" attacks ");
   message.append(defender->description.name);
   message.append(" for (");
   message.append(std::to_string(diceRoll));
   message.append("+");
   message.append(std::to_string(constant));
   message.append(" = ");
   message.append(std::to_string(constant+diceRoll));
   message.append(") damage.");
   gameLog->sendMessage(message);

   defender->stats.health -= (diceRoll + attacker->defaultAttack.damage1.constant);
   if (defender->stats.health <= 0) {
      destroyActor(defender);
   }
}



int ActorManager::wander(ActorEntity* actor) {
	PathingRoute* currentRoute = actor->getCurrentRoute();

	if (currentRoute->hasNextTile()) {
		TileCoords newTile = currentRoute->getNextTile();
		if (map->isTraversibleAt(newTile)) {
			moveActor(actor, newTile);
			currentRoute->incrementProgress();
			return actor->stats.baseMoveSpeed;
		}
	}

	if (rand() % 50 > 2) {
		return actor->stats.baseMoveSpeed;
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
   //find target
   if (!actor->canSeeTarget()) {
      actor->chooseTarget();
   }
   auto targetActor = actor->getTarget();

   //do attack if next to target
   if (actor->location.isAdjacentTo(targetActor->location)) {
      doAttack(actor, targetActor);
      return actor->stats.baseAttackSpeed;
   }

   //continue route if already goies to 
   auto route = actor->getCurrentRoute();
   route->clear();

	Pathfinding::makeLineRoute(actor->location, targetActor->location, map, &LocalMap::isTraversibleAt, route);

	if (route->hasNextTile()) {
      moveActor(actor, route->getNextTile());
      return actor->stats.baseMoveSpeed;
   }

   Pathfinding::makeAStarRoute(actor->location, targetActor->location, map, (*route));
   if (route->hasNextTile()) {
      moveActor(actor, route->getNextTile());
      return actor->stats.baseMoveSpeed;
   }

   
   //this should only be hit if the actor is completely stuck
   return actor->stats.baseMoveSpeed;
}


ActorFactory ActorManager::makeFactory() {
   return ActorFactory(&actorColiseum, &turnQueue, map);
}

TurnQueue* ActorManager::getTurnQueue() {
   return &turnQueue;
}

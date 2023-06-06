#include "Adventure/Scene/AIRunner.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"


void AIRunner::initialize(LocalMap* map, ActorManager* actorMan, ActorUtils* actorUtils) {
   this->map = map;
   this->actorMan = actorMan;
   this->actorUtils = actorUtils;
}


void AIRunner::runActorTurn(ActorEntity *actor) {
	FoV::calcActorFoV(map, actor);

   actor->checkForHostiles();

   int turnTime;
	switch (actor->getState()) {
      case AISTATE_WANDERING:
         turnTime = wander(actor);
         break;
      case AISTATE_APPROACH_AND_WHACK:
         turnTime = approachAndWhack(actor);
      default:
         turnTime = actor->stats.speed;
	}

   actorMan->addActorToTurnQueue(actor, turnTime);
}


int AIRunner::wander(ActorEntity* actor) {
	PathingRoute* currentRoute = actor->getCurrentRoute();

	if (currentRoute->hasNextTile()) {
		TileCoords newTile = currentRoute->getNextTile();
		if (map->isTraversibleAt(newTile)) {
			actorMan->moveActor(actor, newTile);
			currentRoute->incrementProgress();
			return actor->stats.speed;
		}
	}

	if (randomizer.flipCoin()) {
		return actor->stats.speed;
	}

	std::vector<TileCoords>* visibleTiles = actor->getVisibleTiles();
	
	int newTileIndex;
	TileCoords newLocation;

	do {
		newTileIndex = randomizer.getRandomNumber(visibleTiles->size()-1);
		newLocation = visibleTiles->at(newTileIndex);
	} while (!map->isTraversibleAt(newLocation));

	Pathfinding::makeLineRoute(actor->location, visibleTiles->at(newTileIndex), map, &LocalMap::isTraversibleAt, actor->getCurrentRoute());

	return actor->stats.speed;
}



int AIRunner::approachAndWhack(ActorEntity* actor) {
   //find target
   if (!actor->canSeeTarget()) {
      actor->chooseTarget();
   }
   auto targetActor = actor->getTarget();

   //do attack if next to target
   if (actor->location.isAdjacentTo(targetActor->location)) {
      actorUtils->doAttack(actor, actor->getPhysicalWeapon(), targetActor);
      return actor->stats.speed;
   }

   //approach target
   auto route = actor->getCurrentRoute();
   route->clear();

	Pathfinding::makeLineRoute(actor->location, targetActor->location, map, &LocalMap::isTraversibleAt, route);

	if (route->hasNextTile()) {
      actorMan->moveActor(actor, route->getNextTile());
      return actor->stats.speed;
   }

   Pathfinding::makeAStarRoute(actor->location, targetActor->location, map, (*route));
   if (route->hasNextTile()) {
      actorMan->moveActor(actor, route->getNextTile());
      return actor->stats.speed;
   }

   //this should only be hit if the actor is completely stuck
   return actor->stats.speed;
}

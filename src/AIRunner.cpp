#include "Adventure/Scene/AIRunner.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"


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
         turnTime = actor->stats.baseMoveSpeed;
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
			return actor->stats.baseMoveSpeed;
		}
	}

	if (dice.flipCoin()) {
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



int AIRunner::approachAndWhack(ActorEntity* actor) {
   //find target
   if (!actor->canSeeTarget()) {
      actor->chooseTarget();
   }
   auto targetActor = actor->getTarget();

   //do attack if next to target
   if (actor->location.isAdjacentTo(targetActor->location)) {
      actorUtils->doAttack(actor, targetActor);
      return actor->stats.baseAttackSpeed;
   }

   //approach target
   auto route = actor->getCurrentRoute();
   route->clear();

	Pathfinding::makeLineRoute(actor->location, targetActor->location, map, &LocalMap::isTraversibleAt, route);

	if (route->hasNextTile()) {
      actorMan->moveActor(actor, route->getNextTile());
      return actor->stats.baseMoveSpeed;
   }

   Pathfinding::makeAStarRoute(actor->location, targetActor->location, map, (*route));
   if (route->hasNextTile()) {
      actorMan->moveActor(actor, route->getNextTile());
      return actor->stats.baseMoveSpeed;
   }

   
   //this should only be hit if the actor is completely stuck
   return actor->stats.baseMoveSpeed;
}

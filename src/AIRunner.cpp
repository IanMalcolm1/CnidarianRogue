#include "Adventure/Scene/AIRunner.h"
#include "Algorithms/FoV.h"
#include "Algorithms/Pathfinding.h"
#include "Algorithms/PathfindingRoute.h"
#include "Algorithms/PathingSpecs.h"
#include "Entities/Actors/AI.h"
#include "Entities/Actors/ActorEntity.h"
#include "Enums/TurnTime.h"
#include "Logs/DebugLogger.h"


void AIRunner::initialize(LocalMap* map, ActorManager* actorMan, ActorUtils* actorUtils) {
   this->map = map;
   this->actorMan = actorMan;
   this->actorUtils = actorUtils;
}


void AIRunner::runActorTurn(ActorEntity *actor) {
	FoV::calcActorFoV(map, actor);

   int turnTime;
	switch (actor->aiType) {
      case AITYPE_MELEE:
         turnTime = meleeAI(actor);
         break;
      case AITYPE_RANGED:
         turnTime = rangedAI(actor);
      default:
         turnTime = actor->stats.speed;
	}

   actorMan->addActorToTurnQueue(actor, turnTime);
}


int AIRunner::doWander(ActorEntity* actor) {
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

   PathingSpecs specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_NONE);
   specs.start = actor->location;
   specs.end = visibleTiles->at(newTileIndex);

	Pathfinding::calcPath(specs, map, (*actor->getCurrentRoute()));

	return actor->stats.speed;
}



int AIRunner::doApproachAndWhack(ActorEntity* actor) {
   actor->setState(AISTATE_APPROACH_AND_WHACK);
   actor->pickTarget();
   
   if (actor->location == actor->getTargetLastKnownLocation()) {
      actor->setState(AISTATE_IDLE);
      return meleeAI(actor);
   }

   auto targetActor = actor->getTarget();

   //do attack if next to target
   if (actor->location.isAdjacentTo(targetActor->location)) {
      actorUtils->doMeleeAttack(actor, targetActor);
      return actor->stats.speed;
   }

   return doApproachTarget(actor);
}
   
int AIRunner::doShootAndApproach(ActorEntity* actor) {
   actor->setState(AISTATE_SHOOT_AND_APPROACH);
   actor->pickTarget();

   if (actor->location == actor->getTargetLastKnownLocation()) {
      actor->setState(AISTATE_IDLE);
      return meleeAI(actor);
   }

   if (actor->canSeeTarget() && targetIsInShootRange(actor)) {
      actorUtils->doRangedAttack(actor, actor->getTargetLastKnownLocation());
      return actor->stats.speed;
   }

   return doApproachTarget(actor);
 }

int AIRunner::doApproachTarget(ActorEntity* actor) {
   //approach last known location of target
   auto route = actor->getCurrentRoute();
   route->clear();

   PathingSpecs specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_NONE);
   specs.start = actor->location;
   specs.end = actor->getTargetLastKnownLocation();
	Pathfinding::calcPath(specs, map, (*route));

	if (route->hasNextTile()) {
      actorMan->moveActor(actor, route->getNextTile());
      return actor->stats.speed;
   }

   //if hits this point, actor can't find way to get to target
   // this normally means they're being blocked by another actor
   // so they go as close as they can until they get physically blocked
   specs = PathingSpecs(PATH_ROUTE, TRAV_IGNORE_ACTORS);
   specs.start = actor->location;
   specs.end = actor->getTargetLastKnownLocation();
	Pathfinding::calcPath(specs, map, (*route));

	if (route->hasNextTile()) {
      if (map->isTraversibleAt(route->getNextTile())) {
         actorMan->moveActor(actor, route->getNextTile());
         return actor->stats.speed;
      }
   }

   //stuck
   return actor->stats.speed;
}


int AIRunner::meleeAI(ActorEntity* actor) {
   if (actor->isAggroed() || actor->canSeeHostile()) {
      return doApproachAndWhack(actor);
   }

   return doWander(actor);
}

int AIRunner::rangedAI(ActorEntity* actor) {
   if (actor->isAggroed() || actor->canSeeHostile()) {
      return doShootAndApproach(actor);
   }

   return doWander(actor);
}



bool AIRunner::targetIsInShootRange(ActorEntity* actor) {
   ItemEntity* weapon = actor->inventory.getMagicWeapon();

   PathingSpecs specs = PathingSpecs(PATH_LINE, TRAV_IGNORE_NONE);
   specs.lineInfo.range = ((RangedComp*)weapon->getComponent(COMPONENT_RANGED))->range;
   specs.start = actor->location;
   specs.end = actor->getTargetLastKnownLocation();

   testingRoute.clear();
   Pathfinding::calcPath(specs, map, testingRoute);

   if (testingRoute.endTile() == actor->getTargetLastKnownLocation()) {
      return true;
   }
   return false;
}

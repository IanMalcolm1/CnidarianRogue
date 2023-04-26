#include "Entities/ActorFactory.h"
#include "Entities/AI.h"
#include "Entities/ActorEntity.h"


void ActorFactory::registerActor(ActorEntity* actor) {
	map->setActorAt(actor->location, actor);
	turnQueue->insert(actor, 0);
}


ActorEntity* ActorFactory::makeEvilSmileyFace(TileCoords location) {
   ActorEntity* evilSmiley = actorColiseum->makeEntity();
   ActorStatBlock* smileyStats = &evilSmiley->stats;

   smileyStats->maxHealth = 10 + rand()%5;
   smileyStats->health = smileyStats->maxHealth;

   evilSmiley->description.name = "</red:Evil Smiley Face/>";
   evilSmiley->description.desc = "Its insipid grin unnerves you.";

   evilSmiley->display.symbol = ASYM_SMILE_THIN;

   evilSmiley->location = location;

   evilSmiley->faction = FACTION_BAD;

   evilSmiley->addAttackingSubstate(AiState(AISTATE_APPROACH_AND_WHACK));
   
   registerActor(evilSmiley);
   return evilSmiley;
}

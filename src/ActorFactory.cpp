#include "Entities/ActorFactory.h"


void ActorFactory::registerActor(ActorEntity* actor) {
	map->setActorAt(actor->location, actor);
	turnQueue->insert(actor, 0);
}

ActorEntity* ActorFactory::makePlayer() {
   ActorEntity* player = actorColiseum->makeEntity();
   player->isPlayer = true;

   player->stats.maxHealth = 10 + rand()%5;
   player->stats.health = player->stats.maxHealth;

   player->description.name = "The Player";
   player->description.desc = "It's you.";

   player->display.symbol = ASYM_AT;

   registerActor(player);
   return player;
}


ActorEntity* ActorFactory::makeEvilSmileyFace(TileCoords location) {
   ActorEntity* evilSmiley = actorColiseum->makeEntity();
   ActorStatBlock* smileyStats = &evilSmiley->stats;

   smileyStats->maxHealth = 10 + rand()%5;
   smileyStats->health = smileyStats->maxHealth;

   evilSmiley->description.name = "Evil Smiley Face";
   evilSmiley->description.desc = "Its insipid grin unnerves you.";

   evilSmiley->display.symbol = ASYM_SMILE_THIN;

   evilSmiley->location = location;
   
   registerActor(evilSmiley);
   return evilSmiley;
}

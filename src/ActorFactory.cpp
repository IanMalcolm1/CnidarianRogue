#include "Entities/Actors/ActorFactory.h"
#include "Entities/Actors/AI.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Items/ItemFactory.h"
#include "Enums/AsciiSymbols.h"
#include "Enums/TurnTime.h"


void ActorFactory::initialize(EntityColiseum<ActorEntity>* actorColiseum, TurnQueue* turnQueue, LocalMap* map, ItemFactory* itemFactory) {
   this->actorColiseum = actorColiseum;
   this->map = map;
   this->turnQueue = turnQueue;
   this->itemFactory = itemFactory;
}


void ActorFactory::registerActor(ActorEntity* actor) {
	map->setActorAt(actor->location, actor);
	turnQueue->insertActor(actor, 0);
}


ActorEntity* ActorFactory::makeCultistWarrior(TileCoords location) {
   ActorEntity* evilSmiley = actorColiseum->makeEntity();
   ActorStatBlock* smileyStats = &evilSmiley->stats;

   smileyStats->maxHealth = 10 + randomizer.getRandomNumber(5);
   smileyStats->health = smileyStats->maxHealth;
   smileyStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/4;

   evilSmiley->description.name = "Cultist Warrior";
   evilSmiley->description.desc = "It stands hunched and ape-like, mace in hand.";

   evilSmiley->display.symbol = ASYM_LOWER_C;
   evilSmiley->display.symbolColor = colorMap.getColor("maroon");

   evilSmiley->location = location;

   evilSmiley->faction = FACTION_BAD;

   evilSmiley->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_POISON_FANGS));

   evilSmiley->aiType = AITYPE_MELEE;
   
   registerActor(evilSmiley);
   return evilSmiley;
}


ActorEntity* ActorFactory::makeWandCultist(TileCoords location) {
   ActorEntity* evilSmiley = actorColiseum->makeEntity();
   ActorStatBlock* smileyStats = &evilSmiley->stats;

   smileyStats->maxHealth = 10 + randomizer.getRandomNumber(5);
   smileyStats->health = smileyStats->maxHealth;
   smileyStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/4;

   evilSmiley->description.name = "Cultist Preacher";
   evilSmiley->description.desc = "Energy writhes along its distended arms.";

   evilSmiley->display.symbol = ASYM_LOWER_C;
   evilSmiley->display.symbolColor = colorMap.getColor("darkgrey");

   evilSmiley->location = location;

   evilSmiley->faction = FACTION_BAD;

   evilSmiley->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_FIST), itemFactory->getNaturalWeapon(NATWEAP_FORCE_CANTRIP));

   evilSmiley->aiType = AITYPE_RANGED;
   
   registerActor(evilSmiley);
   return evilSmiley;
}

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
   ActorEntity* cultist = actorColiseum->makeEntity();
   ActorStatBlock* cultistStats = &cultist->stats;

   cultistStats->maxHealth = 10 + randomizer.getRandomNumber(5);
   cultistStats->health = cultistStats->maxHealth;
   cultistStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/4;

   cultist->description.name = "Cultist Warrior";
   cultist->description.desc = "It stands hunched and ape-like, mace in hand.";

   cultist->display.symbol = ASYM_LOWER_C;
   cultist->display.symbolColor = colorMap.getColor("maroon");

   cultist->location = location;

   cultist->faction = FACTION_BAD;

   if (randomizer.flipCoin()==0) {
      cultist->inventory.setMeleeWeapon(itemFactory->makeBasicSword({-1,-1}));
   }
   else {
      cultist->inventory.setMeleeWeapon(itemFactory->makeBasicMace({-1,-1}));
   }

   cultist->aiType = AITYPE_MELEE;
   
   registerActor(cultist);
   return cultist;
}


ActorEntity* ActorFactory::makeArmoredCultist(TileCoords location) {
   ActorEntity* cultist = actorColiseum->makeEntity();
   ActorStatBlock* cultistStats = &cultist->stats;

   cultistStats->maxHealth = 13 + randomizer.getRandomNumber(3,5);
   cultistStats->health = cultistStats->maxHealth;
   cultistStats->strength = 1;
   cultistStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/4;

   cultist->description.name = "Cultist Leader";
   cultist->description.desc = "This cultist stands taller than the rest. It wears a set of leather armor.";

   cultist->display.symbol = ASYM_LOWER_C;
   cultist->display.symbolColor = colorMap.getColor("red");

   cultist->location = location;

   cultist->faction = FACTION_BAD;

   cultist->inventory.setMeleeWeapon(itemFactory->makeBasicMace({-1,-1}));
   cultist->inventory.setArmor(itemFactory->makeLeatherArmor({-1,-1}));

   cultist->aiType = AITYPE_MELEE;
   
   registerActor(cultist);
   return cultist;
}


ActorEntity* ActorFactory::makeWandCultist(TileCoords location) {
   ActorEntity* cultist = actorColiseum->makeEntity();
   ActorStatBlock* cultistStats = &cultist->stats;

   cultistStats->maxHealth = 8 + randomizer.getRandomNumber(4);
   cultistStats->health = cultistStats->maxHealth;
   cultistStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/4;

   cultist->description.name = "Cultist Preacher";
   cultist->description.desc = "It grasps a wand in a cage of distended fingers.";

   cultist->display.symbol = ASYM_LOWER_C;
   cultist->display.symbolColor = colorMap.getColor("grey");

   cultist->location = location;

   cultist->faction = FACTION_BAD;

   cultist->inventory.setMagicWeapon(itemFactory->makeForceWand({-1,-1}));

   cultist->aiType = AITYPE_RANGED;
   
   registerActor(cultist);
   return cultist;
}


ActorEntity* ActorFactory::makeBadDog(TileCoords location) {
   ActorEntity* dog = actorColiseum->makeEntity();
   ActorStatBlock* dogStats = &dog->stats;

   dogStats->maxHealth = 5 + randomizer.getRandomNumber(3);
   dogStats->health = dogStats->maxHealth;
   dogStats->speed = FULL_TURN_TIME - FULL_TURN_TIME/4;

   dog->description.name = "Hound";
   dog->description.desc = "Lean muscle covered in coarse fur.";

   dog->display.symbol = ASYM_LOWER_D;
   dog->display.symbolColor = colorMap.getColor("brown");

   dog->location = location;

   dog->faction = FACTION_BAD;

   dog->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_FANGS));

   dog->aiType = AITYPE_MELEE;
   
   registerActor(dog);
   return dog;
}

ActorEntity* ActorFactory::makeSnake(TileCoords location) {
   ActorEntity* snake = actorColiseum->makeEntity();
   ActorStatBlock* snakeStats = &snake->stats;

   snakeStats->maxHealth = 5 + randomizer.getRandomNumber(3);
   snakeStats->health = snakeStats->maxHealth;
   snakeStats->speed = FULL_TURN_TIME;

   snake->description.name = "Snake";
   snake->description.desc = "Scalie noodle.";

   snake->display.symbol = ASYM_LOWER_S;
   snake->display.symbolColor = colorMap.getColor("green");

   snake->location = location;

   snake->faction = FACTION_BAD;

   snake->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_POISON_FANGS));

   snake->aiType = AITYPE_MELEE;
   
   registerActor(snake);
   return snake;
}

#include "Entities/Actors/ActorFactory.h"
#include "Entities/Actors/AI.h"
#include "Entities/Actors/ActorEntity.h"
#include "Entities/Effects/EffectFactory.h"
#include "Entities/Items/ItemFactory.h"
#include "Enums/AsciiSymbols.h"
#include "Enums/TurnTime.h"


void ActorFactory::initialize(EntityColiseum<ActorEntity>* actorColiseum, TurnQueue* turnQueue, LocalMap* map, ItemFactory* itemFactory, EffectManager* effectMan) {
   this->actorColiseum = actorColiseum;
   this->map = map;
   this->turnQueue = turnQueue;
   this->itemFactory = itemFactory;
   this->effectMan = effectMan;
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

   cultist->description.name = "Cultist";
   if (randomizer.flipCoin() == 0) {
      cultist->description.desc = "His skin is pale, verging on translucent. There's something wrong with his tongue.";
   }
   else {
      cultist->description.desc = "Her skin is pale, verging on translucent. There's something wrong with her tongue.";
   }

   cultist->display.symbol = ASYM_LOWER_C;
   cultist->display.symbolColor = colorMap.getColor("grey");

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
   cultist->description.desc = "This cultist is even paler than the rest. Two tongues trail from its mouth.";

   cultist->display.symbol = ASYM_UPPER_C;
   cultist->display.symbolColor = colorMap.getColor("lightgrey");

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
   cultist->description.desc = "It grasps a wand in its pallid fingers.";

   cultist->display.symbol = ASYM_LOWER_P;
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

   dog->description.name = "Cultist Hound";
   dog->description.desc = "It's fur has fallen out, leaving only pallid skin.";

   dog->display.symbol = ASYM_LOWER_D;
   dog->display.symbolColor = colorMap.getColor("grey");

   dog->location = location;

   dog->faction = FACTION_BAD;

   dog->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_FANGS));

   dog->aiType = AITYPE_MELEE;

   registerActor(dog);
   return dog;
}

ActorEntity* ActorFactory::makeCnidas(TileCoords location) {
   ActorEntity* cnidas = actorColiseum->makeEntity();
   ActorStatBlock* cnidasStats = &cnidas->stats;

   cnidasStats->maxHealth = 5 + randomizer.getRandomNumber(3);
   cnidasStats->health = cnidasStats->maxHealth;
   cnidasStats->speed = FULL_TURN_TIME;

   cnidas->description.name = "Cnidas";
   cnidas->description.desc = "Translucent-skinned and wormlike. You realize why the cultists' tongues seemed so... active.";

   cnidas->display.symbol = ASYM_LOWER_S;
   cnidas->display.symbolColor = colorMap.getColor("lightgrey");

   cnidas->location = location;

   cnidas->faction = FACTION_BAD;

   cnidas->inventory = Inventory(itemFactory->getNaturalWeapon(NATWEAP_POISON_SKIN));

   cnidas->aiType = AITYPE_MELEE;

   registerActor(cnidas);
   return cnidas;
}


ActorEntity* ActorFactory::makeCultistIdol(TileCoords location) {
   ActorEntity* cultist = actorColiseum->makeEntity();
   ActorStatBlock* cultistStats = &cultist->stats;

   cultistStats->maxHealth = 17 + randomizer.getRandomNumber(3,7);
   cultistStats->health = cultistStats->maxHealth;
   cultistStats->strength = 3;
   cultistStats->speed = FULL_TURN_TIME + FULL_TURN_TIME/3;

   cultist->description.name = "Cultist Idol";
   cultist->description.desc = "Worms slither beneath its translucent skin, hampering its motion but seemingly providing it great strength.";

   cultist->display.symbol = ASYM_UPPER_I;
   cultist->display.symbolColor = colorMap.getColor("lightgrey");

   cultist->location = location;

   cultist->faction = FACTION_BAD;

   cultist->inventory = Inventory(nullptr, nullptr, itemFactory->getNaturalWeapon(NATWEAP_TOUGH_SKIN));
   cultist->inventory.setMeleeWeapon(itemFactory->makeBigMace({-1,-1}));

   cultist->aiType = AITYPE_MELEE;

   Effect regeneration = EffectFactory::makeRegeneration(1, FULL_TURN_TIME*10000, FULL_TURN_TIME*3);
   effectMan->attachEffect(regeneration, cultist);

   registerActor(cultist);
   return cultist;
}

ActorEntity* ActorFactory::makeHydra(TileCoords location) {
   ActorEntity* hydra = actorColiseum->makeEntity();
   ActorStatBlock* hydraStats = &hydra->stats;

   hydraStats->maxHealth = 30 + randomizer.getRandomNumber(3,5);
   hydraStats->health = hydraStats->maxHealth;
   hydraStats->strength = 3;
   hydraStats->speed = FULL_TURN_TIME;

   hydra->description.name = "Hydra";
   hydra->description.desc = "A massive white worm sits embedded in the ground. Budding clones writhe along its exposed length.";

   hydra->display.symbol = ASYM_YEN;
   hydra->display.symbolColor = colorMap.getColor("offwhite");

   hydra->location = location;

   hydra->faction = FACTION_BAD;

   hydra->inventory = Inventory(nullptr, nullptr, itemFactory->getNaturalWeapon(NATWEAP_TOUGH_SKIN));
   hydra->inventory.setMeleeWeapon(itemFactory->makeBigMace({-1,-1}));

   hydra->aiType = AITYPE_MELEE;

   Effect regeneration = EffectFactory::makeRegeneration(1, FULL_TURN_TIME*10000, FULL_TURN_TIME*3);
   effectMan->attachEffect(regeneration, hydra);

   registerActor(hydra);
   return hydra;
}

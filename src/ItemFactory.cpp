#include "Entities/Items/ItemFactory.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/Items/ItemEntity.h"
#include "Enums/AsciiSymbols.h"
#include "Enums/TurnTime.h"


void ItemFactory::initialize(EntityColiseum<ItemEntity>* coliseum, LocalMap* map) {
   this->coliseum = coliseum;
   this->map = map;
}


void ItemFactory::registerItem(ItemEntity* item, TileCoords location) {
   if (location.x != -1 && location.y != -1) {
      item->location = location;
      map->addItemAt(location, item);
   }
}



/* Weapons */

ItemEntity* ItemFactory::makeBasicSword(TileCoords location) {
   ItemEntity* sword = coliseum->makeEntity();

   sword->description.name = "Sword";
   sword->description.desc = "It's pretty vanilla.";

   sword->display.symbol = ASYM_FORWARD_SLASH;
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 6, 1, 0));
   sword->addComponent(damage, COMPONENT_DAMAGING);

   sword->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(sword, location);
   return sword;
}

ItemEntity* ItemFactory::makeForceWand(TileCoords location) {
   ItemEntity* wand = coliseum->makeEntity();

   wand->description.name = "Force Wand";
   wand->description.desc = "A stick that shoots a ball of force.";

   wand->display.symbol = ASYM_SMALL_DASH;
   wand->display.symbolColor = colorMap.getColor("brown");

   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 3, 1, 0));
   wand->addComponent(damage, COMPONENT_DAMAGING);

   wand->addComponent(RangedComp(10), COMPONENT_RANGED);

   wand->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(wand, location);
   return wand;
}



/* Consumables */

ItemEntity* ItemFactory::makeIntelligenceMushroom(TileCoords location) {
   ItemEntity* mush = coliseum->makeEntity();

   mush->description.name = "Magic Mushroom";
   mush->description.desc = "It has a slight rainbow iridescence.";

   mush->display.symbol = ASYM_UFO;
   mush->display.symbolColor = colorMap.getColor("lavender");

   EffectComp effectComp = EffectComp(effectFactory.makeEnlighten(1));
   mush->addComponent(effectComp, COMPONENT_EFFECT);

   ConsumableComp consumableComp = ConsumableComp(1);
   mush->addComponent(consumableComp, COMPONENT_CONSUMABLE);

   registerItem(mush, location);
   return mush;
}

ItemEntity* ItemFactory::makeStrengthFruit(TileCoords location) {
   ItemEntity* fruit = coliseum->makeEntity();

   fruit->description.name = "Magic Fruit";
   fruit->description.desc = "It looks like a sparkly mango.";

   fruit->display.symbol = ASYM_UFO;
   fruit->display.symbolColor = colorMap.getColor("orange");

   EffectComp effectComp = EffectComp(effectFactory.makeStrengthen(1));
   fruit->addComponent(effectComp , COMPONENT_EFFECT);

   ConsumableComp consumableComp = ConsumableComp(1);
   fruit->addComponent(consumableComp, COMPONENT_CONSUMABLE);

   registerItem(fruit, location);
   return fruit;
}



/* Natural Weapons */

ItemEntity* ItemFactory::getNaturalWeapon(NaturalWeaponType type) {
   if (naturalWeapons[type] != nullptr) {
      return naturalWeapons[type];
   }
   
   switch(type) {
      case NATWEAP_FIST:
         naturalWeapons[NATWEAP_FIST] = makeFists();
         return naturalWeapons[NATWEAP_FIST];

      case NATWEAP_POISON_FANGS:
         naturalWeapons[NATWEAP_POISON_FANGS] = makePoisonFangs();
         return naturalWeapons[NATWEAP_POISON_FANGS];

      case NATWEAP_FORCE_CANTRIP:
         naturalWeapons[NATWEAP_FORCE_CANTRIP] = makeForceCantrip();
         return naturalWeapons[NATWEAP_FORCE_CANTRIP];

      case NUM_NATURALWEAPONS:
         return nullptr;
   }
   return nullptr;
}

ItemEntity* ItemFactory::makeFists() {
   ItemEntity* fists = coliseum->makeEntity();

   fists->description.name = "Fists";
   fists->description.desc = "Hands, wrapped into balls.";

   fists->display.symbol = ASYM_ASTERISK;
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 2, 1, 0));
   fists->addComponent(damage, COMPONENT_DAMAGING);

   fists->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return fists;
}

ItemEntity* ItemFactory::makePoisonFangs() {
   ItemEntity* fangs = coliseum->makeEntity();

   fangs->description.name = "</green:Poisonous Fangs\\>";
   fangs->description.desc = "They look pretty nasty.";

   fangs->display.symbol = ASYM_FAT_ARROW_DOWN;
   fangs->display.symbolColor = colorMap.getColor("green");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 0, 1));
   fangs->addComponent(damage, COMPONENT_DAMAGING);

   EffectComp poisonComp = EffectComp(EffectComp(effectFactory.makePoison(1)));
   fangs->addComponent(poisonComp, COMPONENT_EFFECT);

   fangs->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return fangs;
}

ItemEntity* ItemFactory::makeForceCantrip() {
   ItemEntity* cantrip = coliseum->makeEntity();
   
   cantrip->description.name = "Force Bolt";
   cantrip->description.desc = "A simple combat cantrip."; 

   cantrip->display.symbol = ASYM_ASTERISK;
   cantrip->display.symbolColor = MyColor(255,255,255);

   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 0, 1));
   cantrip->addComponent(damage, COMPONENT_DAMAGING);

   RangedComp range = RangedComp(10);
   cantrip->addComponent(range, COMPONENT_RANGED);

   cantrip->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return cantrip;
}

#include "Entities/Items/ItemFactory.h"
#include "Entities/Components.h"
#include "Enums/AsciiSymbols.h"
#include "Enums/TurnTime.h"


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
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 1, 0));
   sword->addComponent(damage, COMPONENT_DAMAGING);

   registerItem(sword, location);
   return sword;
}



/* Consumables */

ItemEntity* ItemFactory::makeIntelligenceMushroom(TileCoords location) {
   ItemEntity* mush = coliseum->makeEntity();

   mush->description.name = "Magic Mushroom";
   mush->description.desc = "It has a slight rainbow iridescence.";

   mush->display.symbol = ASYM_UFO;
   mush->display.symbolColor = colorMap.getColor("blue");

   EffectComp effect = EffectComp(Effect(EFFECT_PERMANENT, EFFECT_INT_INCREASE, 1));
   mush->addComponent(effect, COMPONENT_EFFECT);

   registerItem(mush, location);
   return mush;
}

ItemEntity* ItemFactory::makeStrengthFruit(TileCoords location) {
   ItemEntity* fruit = coliseum->makeEntity();

   fruit->description.name = "Magic Fruit";
   fruit->description.desc = "It looks like a purple mango";

   fruit->display.symbol = ASYM_UFO;
   fruit->display.symbolColor = colorMap.getColor("purple");

   EffectComp effect = EffectComp(Effect(EFFECT_PERMANENT, EFFECT_STR_INCREASE, 1));
   fruit->addComponent(effect, COMPONENT_EFFECT);

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
         return makeFists();
      case NATWEAP_POISON_FANGS:
         return makePoisonFangs();
      case NUM_NATURALWEAPONS:
         return nullptr;
   }
   return nullptr;
}

ItemEntity* ItemFactory::makeFists() {
   ItemEntity* fists = coliseum->makeEntity();

   fists->description.name = "Fists";
   fists->description.desc = "A pair of flimsy bones wrapped in a thin layer of skin.";

   fists->display.symbol = ASYM_ASTERISK;
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 1));
   fists->addComponent(damage, COMPONENT_DAMAGING);

   return fists;
}

ItemEntity* ItemFactory::makePoisonFangs() {
   ItemEntity* fangs = coliseum->makeEntity();

   fangs->description.name = "</green:Poisonous Fangs/>";
   fangs->description.desc = "They look pretty nasty.";

   fangs->display.symbol = ASYM_FAT_ARROW_DOWN;
   fangs->display.symbolColor = colorMap.getColor("green");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 1));
   fangs->addComponent(damage, COMPONENT_DAMAGING);

   Effect effect = Effect(EFFECT_DOT, EFFECT_POISON, 1, FULL_TURN_TIME*10, FULL_TURN_TIME);
   EffectComp poison = EffectComp(effect);
   fangs->addComponent(effect, COMPONENT_EFFECT);

   return fangs;
}

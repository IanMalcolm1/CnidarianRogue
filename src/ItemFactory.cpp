#include "Entities/Items/ItemFactory.h"


void ItemFactory::registerItem(ItemEntity* item, TileCoords location) {
   item->location = location;
   map->addItemAt(location, item);
}

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


ItemEntity* ItemFactory::makeIntelligenceMushroom(TileCoords location) {
   ItemEntity* mush = coliseum->makeEntity();

   mush->description.name = "Magic Mushroom";
   mush->description.desc = "It has a slight rainbow iridescence.";

   mush->display.symbol = ASYM_UFO;
   mush->display.symbolColor = colorMap.getColor("blue");

   ConsumableComp effect = ConsumableComp(Effect(EFFECT_INT_INCREASE, 1, true));
   mush->addComponent(effect, COMPONENT_CONSUMABLE);

   registerItem(mush, location);
   return mush;
}

ItemEntity* ItemFactory::makeStrengthFruit(TileCoords location) {
   ItemEntity* fruit = coliseum->makeEntity();

   fruit->description.name = "Magic Fruit";
   fruit->description.desc = "It looks like a purple mango";

   fruit->display.symbol = ASYM_UFO;
   fruit->display.symbolColor = colorMap.getColor("purple");

   ConsumableComp effect = ConsumableComp(Effect(EFFECT_STR_INCREASE, 1, true));
   fruit->addComponent(effect, COMPONENT_CONSUMABLE);

   registerItem(fruit, location);
   return fruit;
}

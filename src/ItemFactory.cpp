#include "Entities/Items/ItemFactory.h"
#include "Entities/Actors/ActorStatBlock.h"
#include "Entities/Components.h"
#include "Entities/Damage.h"
#include "Entities/Effects/EffectFactory.h"
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

ItemEntity* ItemFactory::makeBasicDagger(TileCoords location) {
   ItemEntity* dagger = coliseum->makeEntity();

   dagger->description.name = "Dagger";
   dagger->description.desc = "A small blade on a stick.";

   dagger->display.symbol = ASYM_FORWARD_SLASH;
   dagger->display.symbolColor = colorMap.getColor("slategrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 3, 1, 0));
   dagger->addComponent(damage, COMPONENT_DAMAGING);

   dagger->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(dagger, location);
   return dagger;
}

ItemEntity* ItemFactory::makeBasicSword(TileCoords location) {
   ItemEntity* sword = coliseum->makeEntity();

   sword->description.name = "Sword";
   sword->description.desc = "A very long dagger.";

   sword->display.symbol = ASYM_FORWARD_SLASH;
   sword->display.symbolColor = colorMap.getColor("slategrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 4, 1, 0));
   sword->addComponent(damage, COMPONENT_DAMAGING);

   sword->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(sword, location);
   return sword;
}

ItemEntity* ItemFactory::makeBasicMace(TileCoords location) {
   ItemEntity* mace = coliseum->makeEntity();

   mace->description.name = "Mace";
   mace->description.desc = "A metal ball on a stick.";

   mace->display.symbol = ASYM_EXCLAMATION;
   mace->display.symbolColor = colorMap.getColor("slategrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 2, 1, 1));
   mace->addComponent(damage, COMPONENT_DAMAGING);

   mace->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(mace, location);
   return mace;
}

ItemEntity* ItemFactory::makeBigMace(TileCoords location) {
   ItemEntity* mace = coliseum->makeEntity();

   mace->description.name = "Spiked Mace";
   mace->description.desc = "The spikes have a reddish tint. You're not sure it's rust.";

   mace->display.symbol = ASYM_EXCLAMATION;
   mace->display.symbolColor = colorMap.getColor("slategrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 2, 1, 2));
   mace->addComponent(damage, COMPONENT_DAMAGING);

   mace->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   registerItem(mace, location);
   return mace;
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



/* Armor */
ItemEntity* ItemFactory::makeGambeson(TileCoords location) {
   ItemEntity* gambeson = coliseum->makeEntity();

   gambeson->description.name = "Gambeson";
   gambeson->description.desc = "A sturdy jacket made of layered cloth.";

   gambeson->display.symbol = ASYM_AMPERSAND;
   gambeson->display.symbolColor = colorMap.getColor("slategrey");

   gambeson->addComponent(WearableComp(DAMAGE_PHYSICAL,0,0,1), COMPONENT_WEARABLE);

   registerItem(gambeson, location);
   return gambeson;
}

ItemEntity* ItemFactory::makeLeatherArmor(TileCoords location) {
   ItemEntity* armor = coliseum->makeEntity();

   armor->description.name = "Leather Armor";
   armor->description.desc = "Thick leather armor.";

   armor->display.symbol = ASYM_AMPERSAND;
   armor->display.symbolColor = colorMap.getColor("brown");

   armor->addComponent(WearableComp(DAMAGE_PHYSICAL,2,1,0), COMPONENT_WEARABLE);

   registerItem(armor, location);
   return armor;
}




/* Consumables */

ItemEntity* ItemFactory::makeIntelligenceMushroom(TileCoords location) {
   ItemEntity* mush = coliseum->makeEntity();

   mush->description.name = "Magic Mushroom";
   mush->description.desc = "It has a slight rainbow iridescence.";

   mush->display.symbol = ASYM_UFO;
   mush->display.symbolColor = colorMap.getColor("lavender");

   EffectComp effectComp = EffectComp(EffectFactory::makeEnlighten(1));
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

   EffectComp effectComp = EffectComp(EffectFactory::makeStrengthen(1));
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

      case NATWEAP_POISON_SKIN:
         naturalWeapons[NATWEAP_POISON_SKIN] = makePoisonSkin();
         return naturalWeapons[NATWEAP_POISON_SKIN];

      case NATWEAP_CNIDAS_BUDS:
         naturalWeapons[NATWEAP_CNIDAS_BUDS] = makePoisonSkin();
         return naturalWeapons[NATWEAP_CNIDAS_BUDS];

      case NATWEAP_FANGS:
         naturalWeapons[NATWEAP_FANGS] = makeFangs();
         return naturalWeapons[NATWEAP_FANGS];

      case NATWEAP_FORCE_CANTRIP:
         naturalWeapons[NATWEAP_FORCE_CANTRIP] = makeForceCantrip();
         return naturalWeapons[NATWEAP_FORCE_CANTRIP];

      case NATWEAP_TOUGH_SKIN:
         naturalWeapons[NATWEAP_TOUGH_SKIN] = makeToughSkin();
         return naturalWeapons[NATWEAP_TOUGH_SKIN];

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

ItemEntity* ItemFactory::makePoisonSkin() {
   ItemEntity* skin = coliseum->makeEntity();

   skin->description.name = "Poison Skin";
   skin->description.desc = "Slimy.";

   skin->display.symbol = ASYM_DENSE_DOTS;
   skin->display.symbolColor = colorMap.getColor("lightgrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 0, 1));
   skin->addComponent(damage, COMPONENT_DAMAGING);

   EffectComp poisonComp = EffectComp(EffectComp(EffectFactory::makePoison(1)));
   skin->addComponent(poisonComp, COMPONENT_EFFECT);

   skin->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return skin;
}

ItemEntity* ItemFactory::makeFangs() {
   ItemEntity* fangs = coliseum->makeEntity();

   fangs->description.name = "Fangs";
   fangs->description.desc = "They look pretty nasty.";

   fangs->display.symbol = ASYM_FAT_ARROW_DOWN;
   fangs->display.symbolColor = colorMap.getColor("grey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 3, 1, 0));
   fangs->addComponent(damage, COMPONENT_DAMAGING);

   fangs->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return fangs;
}

ItemEntity* ItemFactory::makeForceCantrip() {
   ItemEntity* cantrip = coliseum->makeEntity();
   
   cantrip->description.name = "Force Bolt";
   cantrip->description.desc = "A simple combat cantrip."; 

   cantrip->display.symbol = ASYM_MAGIC;
   cantrip->display.symbolColor = Color(255,255,255);

   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 0, 0, 1));
   cantrip->addComponent(damage, COMPONENT_DAMAGING);

   RangedComp range = RangedComp(10);
   cantrip->addComponent(range, COMPONENT_RANGED);

   cantrip->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return cantrip;
}


ItemEntity* ItemFactory::makeToughSkin() {
   ItemEntity* armor = coliseum->makeEntity();

   armor->description.name = "Tough Skin";
   armor->description.desc = "As strong as leather, but more flexible.";

   armor->display.symbol = ASYM_DENSE_DOTS;
   armor->display.symbolColor = colorMap.getColor("lightgrey");

   armor->addComponent(WearableComp(DAMAGE_PHYSICAL,2,1,0), COMPONENT_WEARABLE);

   return armor;
}

ItemEntity* ItemFactory::makeCnidasBuds() {
   ItemEntity* cnidas = coliseum->makeEntity();

   cnidas->description.name = "Writhing Cnidas";
   cnidas->description.desc = "A swarm of Cnidas budding from the Hydra's body.";

   cnidas->display.symbol = ASYM_DOLLAR;
   cnidas->display.symbolColor = colorMap.getColor("lightgrey");
   
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 4, 1, 0));
   cnidas->addComponent(damage, COMPONENT_DAMAGING);

   EffectComp poisonComp = EffectComp(EffectComp(EffectFactory::makePoison(1)));
   cnidas->addComponent(poisonComp, COMPONENT_EFFECT);

   cnidas->addComponent(WieldableComp(), COMPONENT_WIELDABLE);

   return cnidas;
}

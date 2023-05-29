#include "Entities/Items/ItemDescriber.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"

GameText ItemDescriber::name(ItemEntity* item) {
   return textMaker->makeGameText(EntityDescriber::makeName(item->description.name, item->display));
}

GameText ItemDescriber::describe(ItemEntity* item) {
   return textMaker->makeGameText(item->description.desc);
}

GameText ItemDescriber::describeInDepth(ItemEntity* item) {
   std::string desc = item->description.desc + "\n";

   if (item->hasComponent(COMPONENT_DAMAGING)) {
      desc.append( describeDamage((DamagingComp*) item->getComponent(COMPONENT_DAMAGING)) );
   }

   return textMaker->makeGameText(desc);
}


std::string ItemDescriber::describeDamage(DamagingComp* damage) {
   std::string desc = "Deals " + std::to_string(damage->damage1.dice) + "d6";
   if (damage->damage1.constant != 0) {
      desc.append( "+ " + std::to_string(damage->damage1.constant) + " " );
   }
   desc.append( " " + damageNames[damage->damage1.type] + " damage." );

   return desc;
}


void ItemDescriber::setGameTextMaker(GameTextMaker* gameTextMaker) {
   textMaker = gameTextMaker;
}

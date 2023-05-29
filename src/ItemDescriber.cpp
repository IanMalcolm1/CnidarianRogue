#include "Entities/Items/ItemDescriber.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"

std::string ItemDescriber::describe(ItemEntity* item) {
   std::string desc = EntityDescriber::makeName(item->description.name, item->display);
   desc.append("\n" + item->description.desc);
   
   if (item->hasComponent(COMPONENT_DAMAGING)) {
      DamagingComp* damageComp = (DamagingComp*) item->getComponent(COMPONENT_DAMAGING);
      desc.append( "\n" + describeDamage( damageComp->damage1 ) );
   }

   return desc;
}


std::string ItemDescriber::describeWeapon(ItemEntity* item) {
   std::string desc = EntityDescriber::makeName(item->description.name, item->display);

   DamagingComp* damageComp = (DamagingComp*) item->getComponent(COMPONENT_DAMAGING);
   desc.append( "\n" + describeDamage( damageComp->damage1 ) );

   return desc;
}


std::string ItemDescriber::describeDamage(Damage& damage) {
   std::string desc = "Deals ";

   if (damage.dice != 0) {
      desc.append( std::to_string(damage.dice) + "d6+" );
   }

   desc.append( std::to_string(damage.constant) );

   desc.append( " " + damageNames[damage.type] + " damage." );

   return desc;
}

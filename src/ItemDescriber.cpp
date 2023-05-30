#include "Entities/Items/ItemDescriber.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"

std::string ItemDescriber::describe(ItemEntity* item) {
   std::string desc = EntityDescriber::makeName(item->description.name, item->display);
   desc.append("\n" + item->description.desc);
   
   if (item->hasComponent(COMPONENT_DAMAGING)) {
      DamagingComp* damageComp = (DamagingComp*) item->getComponent(COMPONENT_DAMAGING);
      desc.append("\n" + damageComp->damage1.getDescription());
   }

   if (item->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effectComp = (EffectComp*) item->getComponent(COMPONENT_EFFECT);
      desc.append("\nEffect: " + effectDescriber->describe(effectComp->effect1));
   }

   return desc;
}


std::string ItemDescriber::describeWeapon(ItemEntity* item) {
   std::string desc = EntityDescriber::makeName(item->description.name, item->display);

   DamagingComp* damageComp = (DamagingComp*) item->getComponent(COMPONENT_DAMAGING);
   desc.append("\n" + damageComp->damage1.getDescription());

   if (item->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effectComp = (EffectComp*) item->getComponent(COMPONENT_EFFECT);
      desc.append("\n" + effectDescriber->describe(effectComp->effect1));
   }

   return desc;
}

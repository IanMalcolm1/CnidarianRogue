#include "Entities/Items/ItemDescriber.h"
#include "Entities/Components.h"
#include "Entities/EntityDescriber.h"


void ItemDescriber::initialize(EffectDescriber *effectDescriber) {
   this->effectDescriber = effectDescriber;
}

std::string ItemDescriber::describe(ItemEntity* item) {
   if (item == nullptr) {
      return "";
   }

   std::string desc = EntityDescriber::makeName(item->description.name, item->display);
   desc.append("\n" + item->description.desc);
   desc.append(getComponentDescriptions(item));

   return desc;
}

std::string ItemDescriber::describeMinusDesc(ItemEntity* item) {
   if (item == nullptr) {
      return "";
   }

   std::string desc = EntityDescriber::makeName(item->description.name, item->display);
   desc.append(getComponentDescriptions(item));

   return desc;
}

std::string ItemDescriber::getComponentDescriptions(ItemEntity* item) {
   std::string desc = "";

   if (item->hasComponent(COMPONENT_RANGED)) {
      RangedComp* range = (RangedComp*) item->getComponent(COMPONENT_RANGED);
      desc.append("\nRange "+std::to_string(range->range));
   }
   
   if (item->hasComponent(COMPONENT_DAMAGING)) {
      DamagingComp* damageComp = (DamagingComp*) item->getComponent(COMPONENT_DAMAGING);
      desc.append("\nDeals " + damageComp->damage1.getDescription());
   }

   if (item->hasComponent(COMPONENT_WEARABLE)) {
      WearableComp* wearableComp = (WearableComp*) item->getComponent(COMPONENT_WEARABLE);
      desc.append("\nBlocks " + wearableComp->damage.getDescription());
   }

   if (item->hasComponent(COMPONENT_EFFECT)) {
      EffectComp* effectComp = (EffectComp*) item->getComponent(COMPONENT_EFFECT);
      desc.append("\nEffect: " + effectDescriber->nameAndDescribe(effectComp->effect1));
   }

   return desc;
}

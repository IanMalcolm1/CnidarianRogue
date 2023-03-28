#include "TestItems.h"


/*
TileDisplay* getDisplay() {
   return &display;
}
*/

DescribableComp* ItemData::getDescription() {
   return &description;
};


bool ItemData::hasComponent(ComponentType type) {
   if ((dynamicComponents & type) == type) {
      return true;
   }
   return false;
}


Component* ArmorItemData::getComponent(ComponentType type) {
   if (type == COMPONENT_WEARABLE) {
      return &armor;
   }
   return ItemData::getComponent(type);
}

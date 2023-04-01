#include "EntityItem.h"

Component* EntityItem::getComponent(ComponentType type) {
   if (type == COMPONENT_DESCRIBABLE) {
      //return &description;
   }
   else if (type == COMPONENT_DISPLAY) {
      return &display;
   }
   return Entity::getComponent(type);
}


void EntityItem::removeComponent(ComponentType type) {
   if (type == COMPONENT_DESCRIBABLE ||
         type == COMPONENT_DISPLAY) {
      return;
   }
   
   Entity::removeComponent(type);
}

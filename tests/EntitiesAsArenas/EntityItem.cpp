#include "EntityItem.h"

Component* EntityItem::getComponent(ComponentType type) {
   if (type == COMPONENT_DESCRIPTION) {
      return &description;
   }
   else if (type == COMPONENT_DISPLAY) {
      return &description;
   }
   Entity::getComponent(type);
}


void removeComponent(ComponentType type) {
   if (type == COMPONENT_DESCRIPTION ||
         type == COMPONENT_DISPLAY) {
      return;
   }

   Entity::removeComponent();
}

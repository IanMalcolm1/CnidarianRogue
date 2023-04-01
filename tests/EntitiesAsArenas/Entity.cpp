#include "Entity.h"


bool Entity::hasComponent(ComponentType type) {
   return ((1<<type) & dynamicComponents) == (1<<type);
}

Component* Entity::getComponent(ComponentType type) {
   if (hasComponent(type))
      return componentPtrs[type];

   return nullptr;
}

void Entity::removeComponent(ComponentType type) {
   if (((1<<type) & dynamicComponents) != (1<<type)) {
      return;
   }
   
   if (componentPtrs[type] < (Component*)this || (char*)componentPtrs[type] > (char*)this+bytesUsed) {
      delete componentPtrs[type];
   }
   
   dynamicComponents = dynamicComponents ^ (1<<type);
   componentPtrs[type] = nullptr;
}


Entity::~Entity() {
   for (int i=0; i<NUM_COMPONENT_TYPES; i++) {
      removeComponent((ComponentType) i);
   }
}

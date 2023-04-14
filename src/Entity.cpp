#include "Entities/Entity.h"

int Entity::getId() {
   return id;
}

bool Entity::hasComponent(ComponentType type) {
   return ((1<<type) & componentTypes) == (1<<type);
}

Component* Entity::getComponent(ComponentType type) {
   if (hasComponent(type))
      return componentPtrs[type];

   return nullptr;
}

void Entity::removeComponent(ComponentType type) {
   if (((1<<type) & componentTypes) != (1<<type)) {
      return;
   }
   
   if (componentPtrs[type] < (Component*)this || (char*)componentPtrs[type] > (char*)this+bytesUsed) {
      free(componentPtrs[type]);
   }
   
   componentTypes = componentTypes ^ (1<<type);
   componentPtrs[type] = nullptr;
}

void Entity::reset() {
   for (int i=0; i<NUM_COMPONENT_TYPES; i++) {
      removeComponent((ComponentType) i);
   }
   componentTypes = 0;
   dead = true;
}

Entity::~Entity() {
   reset();
}

void Entity::revive() {
   dead = false;
}


bool Entity::isDead() {
   return dead;
}

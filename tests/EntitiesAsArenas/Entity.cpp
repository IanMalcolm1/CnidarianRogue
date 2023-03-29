#include "Entity.h"


bool Entity::hasComponents(ComponentType types) {
   return ((types & dynamicComponents) == types);
}

Component* Entity::getComponent(ComponentType type) {
   return dynamicComponentPtrs[type];
}

void Entity::removeComponent(ComponentType type) {
   type = (ComponentType) ~type;
   dynamicComponents = dynamicComponents & type;
}

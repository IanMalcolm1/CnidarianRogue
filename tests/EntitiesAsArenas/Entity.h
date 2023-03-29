#pragma once

#include <cstdint>
#include <unordered_map>
#include "../ExampleEntities/TestItems.h"


class Entity {
private:
   int bytesUsed, totalSpace;
   uint32_t dynamicComponents;
   std::unordered_map<ComponentType, Component*> dynamicComponentPtrs;


public:
   int id;

   Entity(int bytesUsed, int totalSpace) : bytesUsed(bytesUsed), totalSpace(totalSpace), dynamicComponents(0),
      dynamicComponentPtrs(std::unordered_map<ComponentType, Component*>()) {};

   bool hasComponents(ComponentType types);
   Component* getComponent(ComponentType type);

   //Currently doesn't actually get rid of data, and therefore leaves
   // some fragmentation. I don't expect to be using this function very
   // often, though.
   void removeComponent(ComponentType type);

   template <typename T>
   void addComponent(T component, ComponentType type) {
      if (sizeof(T) >= totalSpace-bytesUsed) {
         T* ptr = new T();
         (*ptr) = component;
         return;
      }

      T* ptr = this+sizeof(T);
      (*ptr) = component;

      dynamicComponents |= type;      
      dynamicComponentPtrs[type] = ptr;

      bytesUsed += sizeof(T);
   }
};

#pragma once

#include <cstdint>
#include <cstring>
#include <unordered_map>
#include "../ExampleEntities/TestItems.h"


class Entity {
private:
   int bytesUsed, totalSpace;
   uint32_t dynamicComponents;
   std::unordered_map<int, Component*> componentPtrs;


public:
   int id;

   Entity(int bytesUsed, int totalSpace) : bytesUsed(bytesUsed), totalSpace(totalSpace), dynamicComponents(0) {};
   ~Entity();

   bool hasComponent(ComponentType types);
   Component* getComponent(ComponentType type);

   //Currently doesn't actually get rid of data, and therefore leaves
   // some fragmentation. I don't expect to be using this function very
   // often, though.
   void removeComponent(ComponentType type);

   template <typename T>
   void addComponent(T component, ComponentType type) {
      if (hasComponent(type)) {
         return;
      }

      if (sizeof(T) >= totalSpace-bytesUsed) {
         T* externalComponent = new T(component);
         componentPtrs[type] = (Component*) externalComponent;
         dynamicComponents |= (1 << type);      
         return;
      }


      char* dst = (char*) this+bytesUsed;
      std::memcpy(dst, &component, sizeof(T));

      dynamicComponents |= (1 << type);      
      componentPtrs[type] = (Component*) dst;
      bytesUsed += sizeof(T);
   }
};

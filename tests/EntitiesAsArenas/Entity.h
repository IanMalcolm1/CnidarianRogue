#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include "TestComponents.h"


class Entity {
private:
   int id;
   int bytesUsed, totalSpace;
   uint32_t componentTypes;
   //std::unordered_map<int, Component*> componentPtrs;
   // Testing if a vector will stop valgrind whining
   std::vector<Component*> componentPtrs;


public:
   Entity(int id, int bytesUsed, int totalSpace) : id(id), bytesUsed(bytesUsed), totalSpace(totalSpace), componentTypes(0), componentPtrs(std::vector<Component*>(NUM_COMPONENT_TYPES, nullptr)) {
      bytesUsed += (8-(bytesUsed & 0b111)); //alignment
   };
   ~Entity();

   int getId();
   bool hasComponent(ComponentType types);
   Component* getComponent(ComponentType type);

   /* Currently doesn't actually get rid of data, and therefore leaves
    * some internal fragmentation. I don't expect to be using this function very
    * often, though */
   void removeComponent(ComponentType type);

    /* Components holding complicated data structures with pointers are 
    * NOT ALLOWED. Otherwise there's no easy way to implement deallocation.
    * If you need a string, vector, etc, add them as member variables to
    * a derived class.*/
   template <typename T>
   void addComponent(T component, ComponentType type) {
      if (hasComponent(type)) {
         return;
      }

      if (sizeof(T) > totalSpace-bytesUsed) {
         T* externalComponent = (T*) malloc(sizeof(T));
         std::memcpy(externalComponent, &component, sizeof(T));

         componentPtrs[type] = (Component*) externalComponent;
         componentTypes |= (1 << type);      
         return;
      }


      char* dst = (char*) this+bytesUsed;
      std::memcpy(dst, &component, sizeof(T));

      componentTypes |= (1 << type);      
      componentPtrs[type] = (Component*) dst;
      bytesUsed += sizeof(T);
      bytesUsed += (8-(bytesUsed & 0b111)); //alignment
   }

   void reset();
};

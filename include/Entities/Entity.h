#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include "Entities/Components.h"

/* An Entity (so far as I've designed them for this program)
 * is essentially a data arena that allows for the addition
 * and removal of variably-sized, c-style structs at runtime.
 * It is recommended that Enitities not be created manually,
 * and instead be allocated automatically by an
 * EntityColiseum object. Otherwise the actual data arena
 * controlled by the entity will need to be allocated
 * manually.
 *
 * Note 1: Components should not contain pointers, whether
 * directly or via a class such as std::string or
 * std::vector. Neither should components contain their
 * own logic.
 *
 * Note 2: Unless it exceeded the Entity's allocated space 
 * and was thus allocated randomly to the heap, removing
 * a component neither deletes its data nor repacks
 * remaining components. I am making an assumption that
 * additions will be more common than removals.
 */

class Entity {
private:
   int id; //Corresponds to index in an EntityColiseum
   int bytesUsed, totalSpace;
   bool dead; //Dead = slot was reset, and is unused
   uint32_t componentTypes;
   std::vector<Component*> componentPtrs;


public:
   Entity(int id, int bytesUsed, int totalSpace) : id(id), bytesUsed(bytesUsed), totalSpace(totalSpace), componentTypes(0), componentPtrs(std::vector<Component*>(NUM_COMPONENT_TYPES, nullptr)), dead(false) {
      bytesUsed += (8-(bytesUsed & 0b111)); //alignment
   };
   ~Entity();

   int getId();
   bool isDead();
   void revive();
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

#pragma once

#include "Entity.h"
#include <cstddef>
#include <cstdlib>
#include <cwchar>


#define EXTRA_BYTES 64

/* WARNING: This number is tied to some manually-implemented
 * bitshifts, and should be changed with caution */
#define ENTITIES_PER_ARENA 32
//should be log2 of ENTITIES_PER_ARENA
#define BITSHIFTS_FOR_DIVISION 5
#define MASK_FOR_REMAINDER 0b11111


template <typename EType>
class EntityColiseum {
private:
   int bytesPerEntity;
   int dirtySlots;
   std::vector<int> reusableSlots;
   std::vector<void*> arenas;

public:
   EntityColiseum() : bytesPerEntity(sizeof(EType)+EXTRA_BYTES),
      dirtySlots(0), reusableSlots(std::vector<int>()),
      arenas(std::vector<void*>()) {
         bytesPerEntity += (8-(bytesPerEntity & 0b111)); //alignment
      };

   ~EntityColiseum() {
      for (int i =0; i<dirtySlots; i++) {
         getEntity(i)->~EType();
      }

      for (void* ptr : arenas) {
         free(ptr);
      }
   };


   EType* makeEntity() {
      if (reusableSlots.size() > 0) {
         int i = reusableSlots.back();
         reusableSlots.pop_back();

         char* slotPtr = (char*) arenas[i >> BITSHIFTS_FOR_DIVISION];
         slotPtr += bytesPerEntity*(i&MASK_FOR_REMAINDER);

         return (EType*) slotPtr;
      }

      if ((dirtySlots&MASK_FOR_REMAINDER)==0 &&
      (dirtySlots >> BITSHIFTS_FOR_DIVISION) >= arenas.size()) {
         arenas.push_back(malloc(bytesPerEntity<<BITSHIFTS_FOR_DIVISION));
      }

      char* dest = (char*) arenas[dirtySlots>>BITSHIFTS_FOR_DIVISION];
      dest += bytesPerEntity*(dirtySlots&MASK_FOR_REMAINDER);

      EType* newEntity = new(dest) EType(dirtySlots, sizeof(EType), bytesPerEntity);

      dirtySlots++;

      return newEntity;
   };


   EType* getEntity(int id) {
      char* ptr = (char*) arenas[id>>BITSHIFTS_FOR_DIVISION];
      ptr += bytesPerEntity*(id&MASK_FOR_REMAINDER);

      return (EType*) ptr;
   };

   void deleteEntity(int id) {
      getEntity(id)->reset();
      reusableSlots.push_back(id);
   };
};

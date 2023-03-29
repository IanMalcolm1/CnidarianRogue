#pragma once

#include "Entity.h"
#include <cstddef>
#include <cstdlib>
#include <cwchar>


#define EXTRA_BYTES 160

/* WARNING: This number is tied to some manually-implemented
 * bitshifts, and should be changed with caution */
#define ENTITIES_PER_ARENA 32
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
      arenas(std::vector<void*>()) {};


   EType* makeEntity() {
      if (reusableSlots.size() > 0) {
         int i = reusableSlots.back();
         reusableSlots.pop_back();

         EType* ptr = (EType*) arenas[i >> BITSHIFTS_FOR_DIVISION];
         ptr += bytesPerEntity*(i&MASK_FOR_REMAINDER);

         (ptr) = EType(sizeof(EType), bytesPerEntity);

         return ptr;
      }

      if ((dirtySlots&MASK_FOR_REMAINDER)==0 &&
      (dirtySlots >> BITSHIFTS_FOR_DIVISION) >= arenas.size()) {
         arenas.push_back(malloc(bytesPerEntity>>BITSHIFTS_FOR_DIVISION));
      }

      EType* ptr = (EType*) arenas[dirtySlots>>BITSHIFTS_FOR_DIVISION];
      ptr += bytesPerEntity*(dirtySlots&MASK_FOR_REMAINDER);

      dirtySlots++;

      (ptr) = EType(sizeof(EType), bytesPerEntity);

      return ptr;
   };


   EType* get(int id) {
      EType* ptr = (EType*) arenas[id>>BITSHIFTS_FOR_DIVISION];
      ptr += bytesPerEntity*(id&MASK_FOR_REMAINDER);

      return ptr;
   };

   void deleteItem(int id) {
      reusableSlots.push_back(id);
   };
};

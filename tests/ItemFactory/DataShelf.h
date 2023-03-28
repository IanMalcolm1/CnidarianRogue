#pragma once

#include <utility>
#include <vector>

/* Name based on assumpton that these will be managed by 
 * a class with Warehouse/Store/Mart in the name */

template <typename DataType>
class DataShelf {
   private:
      int arraySize;
      int dirtySlots;
      std::vector<int> reusableSlots;
      std::vector<DataType*> arrays;
      
   public:
      DataShelf(int arraySize = 64) : arraySize(arraySize),
         dirtySlots(0), reusableSlots(std::vector<int>()),
         arrays(std::vector<DataType*>()) {
            arrays.push_back(new DataType[arraySize]);
         };

      ~DataShelf() {
         for (DataType* array : arrays) {
            delete[] array;            
         }
      }



      /* Returns a pointer to the stored item, and an id for
       * use when deleting the item from the shelf */
      std::pair<DataType*, int> add(DataType item) {
         if (reusableSlots.size()>0) {
            int i = reusableSlots.back();
            arrays[i/arraySize][i%arraySize] = item;
            reusableSlots.pop_back();
            return std::make_pair(&arrays[i/arraySize][i%arraySize], i);
         }

         if (dirtySlots%arraySize==0) {
            if (dirtySlots/arraySize >= arrays.size()) {
               arrays.push_back(new DataType[arraySize]);
            }
         }

         arrays[dirtySlots/arraySize][dirtySlots%arraySize] = item;
         dirtySlots++;
         return std::make_pair(&arrays[(dirtySlots-1)/arraySize][(dirtySlots-1)%arraySize], dirtySlots-1);
      }



      DataType* get(int id) {
          return &arrays[id/arraySize][id%arraySize];
      }



      /* Takes the id returned when the item was added to
       * the shelf */
      void deleteItem(int index) {
         reusableSlots.push_back(index);
      }
};

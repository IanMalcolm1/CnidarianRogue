#include "DataShelf.h"
#include "TestActor.h"
#include <iostream>
#include <vector>


int main() {
   DataShelf<HumanoidActorData> shelf = DataShelf<HumanoidActorData>();

   std::vector<int> ids = std::vector<int>();

   HumanoidActorData carl = HumanoidActorData();
   carl.name = "Carl";

   for (int i=0; i<300; i++) {
      if (i%20 == 0) {
         auto pair = shelf.add(carl);
         ids.push_back(pair.second);
         continue;
      }
      
      shelf.add(carl);
   }

   for (int id : ids) {
      shelf.deleteItem(id);
   }

   std::cout << "\nExpected: 280, 260, 240, ..., 0\n";

   for (int i=0; i<ids.size(); i++) {
      auto pair = shelf.add(carl);
      std::cout << pair.second << ", ";
   }




   HumanoidActorData steveData = HumanoidActorData();
   steveData.name = "Steve";

   Actor steve = Actor();

   auto pair = shelf.add(steveData);

   HumanoidActorData* steveDataPtr = pair.first;
   steveDataPtr->id = pair.second;

   steve.data = steveDataPtr;

   steveDataPtr = nullptr;
   steveDataPtr = (HumanoidActorData*) steve.data;

   std::cout << "\nExpected: " << steveData.name.c_str() << ", " << pair.second;
   std::cout << "\nActual: " << steveDataPtr->name.c_str() << ", " << steveDataPtr->id;

   std::cout << "\nDone\n";
}

#include <iostream>
#include <unordered_map>
#include "../ExampleEntities/TestItems.h"

int main() {
   std::cout << "~ Size Tests ~\n";
   std::cout << "Wearable: " << sizeof(WearableComp) << '\n';
   WearableComp wearable = WearableComp();
   std::cout << "Wearable from Object: " << sizeof(wearable) << '\n';

   std::cout << "ItemData: " << sizeof(ItemData) << '\n';

   std::cout << "DescribableComp: " << sizeof(DescribableComp) << '\n';

   std::cout << "unordered_map: " << sizeof(std::unordered_map<ComponentType, Component*>) << '\n';
   std::cout << "vector: " << sizeof(std::vector<Component*>) << '\n';


   std::vector<Component*> testVec = std::vector<Component*>();
   std::cout << "vector object: " << sizeof(testVec) << '\n';
   for (int i=0; i<20; i++) {
      testVec.push_back(nullptr);
   }
   std::cout << "vector object after push_back()s: " << sizeof(testVec) << '\n';



   std::cout << "string: " << sizeof(std::string) << " (apparently modern strings contain 16-char buffers to avoid heap allocation when possible)\n";


}

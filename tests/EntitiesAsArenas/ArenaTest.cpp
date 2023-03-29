#include <iostream>
#include <unordered_map>
#include "../ExampleEntities/TestItems.h"

struct A {
   int num1, num2, num3;
};

struct B : public A {
   int num;
};


int getSize(A* ptr) {
   return sizeof((*ptr));
};


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


   std::cout << "TileDisplay: " << sizeof(TileDisplay) << '\n';

   
   /* These two tests seem to indicate I need to use templates to get proper sizes
    * hmmmm */
   A* aPtrToBObj = new B();
   std::cout << "A ptr to B object size: " << getSize(aPtrToBObj) << " (A has size 12, B has size 16)\n";
   std::cout << "Same as above, but buggy: " << sizeof(aPtrToBObj) << '\n';


   int num0 = 32;
   int num1 = 33;
   int num2 = 31;
   int num3 = 68;

   std::cout << "32 bitshift 5: " << (num0 >> 5) << '\n';
   std::cout << "33 bitshift 5: " << (num1 >> 5) << '\n';
   std::cout << "31 bitshift 5: " << (num2 >> 5) << '\n';
   std::cout << "68 bitshift 5: " << (num3 >> 5) << '\n';

   int mask = 0b11111;

   std::cout << "32 masked: " << (num0 & mask) << '\n';
   std::cout << "33 masked: " << (num1 & mask) << '\n';
   std::cout << "31 masked: " << (num2 & mask) << '\n';
   std::cout << "68 masked: " << (num3 & mask) << '\n';
}

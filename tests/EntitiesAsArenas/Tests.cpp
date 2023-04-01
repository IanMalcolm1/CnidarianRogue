#include "Tests.h"
#include "Entity.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>



void testDynamicAllocation() {
   void* arena = malloc(256);

   //Copying a component to the arena
   void* destPtr = arena;

   DurabilityComp durability = DurabilityComp(250, 19);

   std::memcpy(destPtr, &durability, sizeof(DurabilityComp));

   DurabilityComp* durPtr = (DurabilityComp*) arena;

   std::cout << durPtr->current << ", " << durPtr->total << '\n';


   //Copying a component to the arena + ptr addition
   destPtr = (DurabilityComp*)arena+sizeof(DurabilityComp);

   DurabilityComp dur2 = DurabilityComp(45,6);

   std::memcpy(destPtr, &dur2, sizeof(DurabilityComp));

   DurabilityComp* durPtr2 = (DurabilityComp*) destPtr;

   std::cout << durPtr2->current << ", " << durPtr2->total << '\n';

   free(arena);
}



void testEntities() {
   //Space for entity, description, and durability
   size_t space = sizeof(Entity)+sizeof(DescribableComp)+sizeof(DurabilityComp);
   void* arena = malloc(space);

   Entity* entityPtr = (Entity*) arena;
   {
      (*entityPtr) = Entity(sizeof(Entity), space);
   }


   //Adding a durability component
   std::cout << "Has component: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';

   DurabilityComp durability = DurabilityComp(250, 19);
   entityPtr->addComponent(durability, COMPONENT_DURABILITY);

   std::cout << "Has component: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';

   DurabilityComp* durPtr = (DurabilityComp*) entityPtr->getComponent(COMPONENT_DURABILITY);

   std::cout << "Component Values (actual, expected): (" << durPtr->total << ", " << durability.total << "), (" << durPtr->current << ", " << durability.current << ")\n";

   
   //Adding a describable component
   DescribableComp description = DescribableComp("testname", "testDescription");

   entityPtr->addComponent(description, COMPONENT_DESCRIBABLE);

   DescribableComp* descPtr = (DescribableComp*) entityPtr->getComponent(COMPONENT_DESCRIBABLE);

   std::cout << "\nComponent Values (actual, expected): (" << descPtr->name << ", " << description.name << "), (" << descPtr->desc << ", " << description.desc << ")\n";


   //Removing the durability component
   entityPtr->removeComponent(COMPONENT_DURABILITY);

   std::cout << "\nHas durability component?: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';
   

   //Adding a third component. Should take it over the allocated space
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 3, 2));
   entityPtr->addComponent(damage, COMPONENT_DAMAGING);
   DamagingComp* damPtr = (DamagingComp*) entityPtr->getComponent(COMPONENT_DAMAGING);

   std::cout << "\nComponent Values (actual, expected): (" << damPtr->damage1.type << ", " << DAMAGE_PHYSICAL << "), (" << damPtr->damage1.dice << ", " << 3 << "), (" << damPtr->damage1.constant << ", " << 2 << ")\n";


   std::cout << "\nVarious pointers. One should be outside the arena bounds";
   std::cout << "\nEntityPtr: " << entityPtr;
   std::cout << "\nSpace in arena: " << space;
   std::cout << "\nDescribablePtr: " << descPtr;
   std::cout << "\nDurabilityPtr: " << durPtr;
   std::cout << "\nDamagingPtr: " << damPtr << '\n';

   entityPtr->~Entity();

   free(arena);
}



void testColiseums() {
   EntityColiseum<EntityItem> coliseum = EntityColiseum<EntityItem>();

   EntityItem* item1 = coliseum.makeEntity();
   WearableComp wearable = WearableComp(3, 1);
   DurabilityComp durability = DurabilityComp(256, 128);

   item1->addComponent(wearable, COMPONENT_WEARABLE);
   item1->addComponent(durability, COMPONENT_DURABILITY);


   WearableComp* wearablePtr = (WearableComp*) item1->getComponent(COMPONENT_WEARABLE);
   DurabilityComp* durabilityPtr = (DurabilityComp*) item1->getComponent(COMPONENT_DURABILITY);


}



int getSize(A* ptr) {
   return sizeof((*ptr));
};


void sizeAndPointersTests() {
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

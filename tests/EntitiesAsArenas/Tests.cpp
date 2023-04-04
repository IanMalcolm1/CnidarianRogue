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


   //testing overwriting new (doesn't seem too feasible)
   /*
   Description* descPtr = new Description("test1", "test1");
   Description* testDesc = new(descPtr) Description("test2", "test2");
   std::cout << "Should be test2: " << descPtr->name << ", " << testDesc->name <<'\n';

   
   delete descPtr;

   char* fuckery = (char*) descPtr;
   Description* partialOverwrite = new(fuckery) Description("test3","test3");
   std::cout << "Should be test3: " << partialOverwrite->name << '\n';

   delete fuckery;
   */

   free(arena);
}



void testEntities() {
   //Space for entity, description, and durability
   size_t space = sizeof(Entity)+sizeof(WearableComp)+sizeof(DurabilityComp);
   void* arena = malloc(space);

   Entity* entityPtr = (Entity*) arena;
   (*entityPtr) = Entity(0, sizeof(Entity), space);


   //Adding a durability component
   std::cout << "Has component: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';

   DurabilityComp durability = DurabilityComp(250, 19);
   entityPtr->addComponent(durability, COMPONENT_DURABILITY);

   std::cout << "Has component: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';

   DurabilityComp* durPtr = (DurabilityComp*) entityPtr->getComponent(COMPONENT_DURABILITY);

   std::cout << "Component Values (actual, expected): (" << durPtr->total << ", " << durability.total << "), (" << durPtr->current << ", " << durability.current << ")\n";

   
   //Adding a wearable component
   WearableComp wearable = WearableComp(4,5);
   entityPtr->addComponent(wearable, COMPONENT_WEARABLE);
   WearableComp* wearPtr = (WearableComp*) entityPtr->getComponent(COMPONENT_WEARABLE);

   std::cout << "\nComponent Values (actual, expected): (" << wearPtr->dice << ", " << wearable.dice << "), (" << wearPtr->constant << ", " << wearable.constant << ")\n";


   //Removing the durability component
   entityPtr->removeComponent(COMPONENT_DURABILITY);

   std::cout << "\nHas durability component?: " << entityPtr->hasComponent(COMPONENT_DURABILITY) << '\n';
   

   //Adding a third component. Should take it over the allocated space
   DamagingComp damage = DamagingComp(Damage(DAMAGE_PHYSICAL, 3, 2));
   entityPtr->addComponent(damage, COMPONENT_DAMAGING);
   DamagingComp* damPtr = (DamagingComp*) entityPtr->getComponent(COMPONENT_DAMAGING);

   std::cout << "\nComponent Values (actual, expected): (" << damPtr->damage1.type << ", " << DAMAGE_PHYSICAL << "), (" << damPtr->damage1.dice << ", " << 3 << "), (" << damPtr->damage1.constant << ", " << 2 << ")\n";


   //Testing that components that would exceed space get placed properly
   std::cout << "\nPointers to components, in the order they were added. DamagingPtr (and WearablePtr now I've added alignment stuff) should be out of the entity's arena bounds. (Durability was 'removed' before Damaging was added to this entity, but that just removes the entity's pointer to its location, and does not clear the space or reuse it.)";
   std::cout << "\nEntityPtr: " << (long)entityPtr;
   std::cout << "\nSpace in arena: " << space;
   std::cout << "\nDurabilityPtr: " << (long)durPtr;
   std::cout << "\nWearablePtr: " << (long)wearPtr;
   std::cout << "\nDamagingPtr: " << (long)damPtr << '\n';


   //Alignment tests
   std::cout << "\nAlignment tests (pointer addresses mod 8)";
   std::cout << "\narena/entity: " << (long)arena%8;
   std::cout << "\ndurabilityPtr: " << (long)durPtr%8;
   std::cout << "\nwearablePtr: " << (long)wearPtr%8;
   std::cout << "\ndamagePtr: " << (long)damPtr%8 << '\n';

   entityPtr->~Entity();

   free(arena);
}



void testColiseums() {
   EntityColiseum<EntityItem> coliseum = EntityColiseum<EntityItem>();

   EntityItem* item1 = coliseum.makeEntity();
   WearableComp wearable = WearableComp(3, 1);
   DurabilityComp durability = DurabilityComp(256, 128);

   item1->addComponent(durability, COMPONENT_DURABILITY);
   item1->addComponent(wearable, COMPONENT_WEARABLE);


   WearableComp* wearablePtr = (WearableComp*) item1->getComponent(COMPONENT_WEARABLE);
   DurabilityComp* durabilityPtr = (DurabilityComp*) item1->getComponent(COMPONENT_DURABILITY);

   std::cout << "Testing that components worked for a single entity in the arena. (Expected, Actual)\n";
   std::cout << "Wearable: (" << wearable.dice << ", " << wearablePtr->dice << "), (" << wearable.constant << ", " << wearablePtr->constant << ")\n";
   std::cout << "Durability: (" << durability.current<< ", " << durabilityPtr->current << "), (" << durability.total << ", " << durabilityPtr->total << ")\n";


   std::vector<int> expectedValues = std::vector<int>();
   std::vector<EntityItem*> items = std::vector<EntityItem*>();

   for (int i=0; i<72; i++) {
      expectedValues.push_back(rand()%512);
      DurabilityComp tempDurability = DurabilityComp(expectedValues[i], 0);
      items.push_back(coliseum.makeEntity());
      items[i]->addComponent(tempDurability, COMPONENT_DURABILITY);
      
   }

   for (int i=0; i<72; i++) {
      DurabilityComp* dur = (DurabilityComp*) items[i]->getComponent(COMPONENT_DURABILITY);
      if (dur->total != expectedValues[i]) {
         std::cout << "\nTest failed at item " << i << "\n\t Expected, Actual: " << expectedValues[i] << ", " << dur->total;
      }
      if ((long)items[i]%8 != 0) {
         std::cout << "Entity " << i << "not aligned. Off by " << (long)items[i]%8;
      }
   }
   std::cout << "\nEnd of 72 new entities test";

   coliseum.deleteEntity(33);

   EntityItem* replacementEntity = coliseum.makeEntity();
   std::cout << "\n\nReplacement id = " << replacementEntity->getId() << " (should be 33)";
   replacementEntity->addComponent(wearable, COMPONENT_WEARABLE);
   wearablePtr = (WearableComp*) replacementEntity->getComponent(COMPONENT_WEARABLE);
   std::cout << "\nReplacement wearable component stats: " << wearablePtr->dice << " (expected 3), " << wearablePtr->constant << " (expected 1)\n";
}



int getSize(A* ptr) {
   return sizeof((*ptr));
};


void sizeAndPointersTests() {
   std::cout << "~ Size Tests ~\n";
   std::cout << "Wearable: " << sizeof(WearableComp) << '\n';
   WearableComp wearable = WearableComp();
   std::cout << "Wearable from Object: " << sizeof(wearable) << '\n';

   std::cout << "ItemData: " << sizeof(EntityItem) << '\n';

   std::cout << "DescribableComp: " << sizeof(Description) << '\n';

   std::cout << "unordered_map: " << sizeof(std::unordered_map<ComponentType, Component*>) << '\n';
   std::cout << "vector: " << sizeof(std::vector<Component*>) << '\n';

   std::cout << "Char, Int struct: " << sizeof(CharInt) << '\n';
   std::cout << "Int, Char struct: " << sizeof(IntChar) << '\n';


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
   delete aPtrToBObj;


   int num0 = 32;
   int num1 = 33;
   int num2 = 31;
   int num3 = 68;

   std::cout << "\n32 bitshift 5: " << (num0 >> 5) << '\n';
   std::cout << "33 bitshift 5: " << (num1 >> 5) << '\n';
   std::cout << "31 bitshift 5: " << (num2 >> 5) << '\n';
   std::cout << "68 bitshift 5: " << (num3 >> 5) << '\n';

   int mask = 0b11111;

   std::cout << "32 masked: " << (num0 & mask) << '\n';
   std::cout << "33 masked: " << (num1 & mask) << '\n';
   std::cout << "31 masked: " << (num2 & mask) << '\n';
   std::cout << "68 masked: " << (num3 & mask) << '\n';
}

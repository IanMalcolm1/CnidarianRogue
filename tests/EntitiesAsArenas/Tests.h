#include "EntityColiseum.h"
#include "EntityItem.h"
#include "../ExampleEntities/TestItems.h"

struct A {
   int num1, num2, num3;
};

struct B : public A {
   int num;
};

int getSize(A* ptr);
void sizeAndPointersTests();

void testEntities();

void testDynamicAllocation();

void testColiseums();

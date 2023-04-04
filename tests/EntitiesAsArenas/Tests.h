#include "EntityColiseum.h"
#include "EntityItem.h"
#include "TestComponents.h"

struct A {
   int num1, num2, num3;
};

struct B : public A {
   int num;
};

struct CharInt {
   char character;
   int test;
};

struct IntChar {
   int testi;
   char testc;
};

int getSize(A* ptr);
void sizeAndPointersTests();

void testEntities();

void testDynamicAllocation();

void testColiseums();

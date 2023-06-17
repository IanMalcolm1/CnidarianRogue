#include "TurnQueue.h"
#include <iostream>
#include <string>


void printNode(TurnQueueNode* node) {
   std:: cout << "next: " << std::to_string(node->next);
   std:: cout << " | time: " << std::to_string(node->time);
   std::string isActor = node->isActor ? "true" : "false";
   std::cout << " | isActor: " << isActor;
   std::cout << " | actor: " << std::to_string(node->actor->id);
   std::cout << " | effect: " << node->effect.id;
   std::cout << '\n';
}

void printArr(int* arr, int length) {
   std::cout << "[";
   for (int i=0; i<length-1; i++) {
      std::cout << std::to_string(arr[i]) + ", ";
   }
   std::cout << std::to_string(arr[length-1]) + "]";
}

void printFailMessage(int* expected, int* actual, int length) {
      std::cout << "Failed >:(\nExpected: ";
      printArr(expected, length);
      std::cout << "\nActual:   ";
      printArr(actual, length);
      std::cout << "\n\n";
}

void testOne(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 1: Inserting actors at same turn time\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int numActors = 5;
   int expected[] = {0,1,2,3,4};
   int actual[numActors];


   for (int i=0; i<numActors; i++) {
      testQueue.insertActor(&actors[i], 42);
   }

   for (int i=0; i<numActors; i++) {
      TurnQueueNode* node = testQueue.pop();
      if (node->actor->id != i) {
         passed = false;
      }
      actual[i] = node->actor->id;
   }

   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, numActors);
   }
}


void testTwo(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 2: Popping then inserting actor nodes\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int arrLength = 4;
   int expected[] = {1,2,0,3};
   int actual[arrLength];

   testQueue.insertActor(&actors[0], 40);
   testQueue.insertActor(&actors[1], 20);

   auto node = testQueue.pop();
   actual[0] = node->actor->id;
   if (actual[0] != expected[0]) {
      passed = false;
   }

   testQueue.insertActor(&actors[2], 10);
   testQueue.insertActor(&actors[3], 30);

   for (int i=1; i<arrLength; i++) {
      node = testQueue.pop();
      actual[i] = node->actor->id;
      if (actual[0] != expected[0]) {
         passed = false;
      }
   }

   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, arrLength);
   }
}


void testThree(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 3: Popping then inserting entity nodes\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int arrLength = 4;
   int expected[] = {1,2,0,3};
   int actual[arrLength];

   Effect testEffect = Effect();

   testQueue.insertEffect(testEffect, &actors[0], 40);
   testQueue.insertEffect(testEffect, &actors[1], 20);

   auto node = testQueue.pop();
   actual[0] = node->actor->id;
   if (actual[0] != expected[0]) {
      passed = false;
   }

   testQueue.insertEffect(testEffect, &actors[2], 10);
   testQueue.insertEffect(testEffect, &actors[3], 30);

   for (int i=1; i<arrLength; i++) {
      node = testQueue.pop();
      actual[i] = node->actor->id;
      if (actual[0] != expected[0]) {
         passed = false;
      }
   }

   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, arrLength);
   }
}



void testFour(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 4: Removing actor node\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int arrLength = 3;
   int expected[] = {0,2,3};
   int actual[arrLength];

   testQueue.insertActor(&actors[0], 42);
   testQueue.insertActor(&actors[1], 42);
   testQueue.insertActor(&actors[2], 42);

   testQueue.removeActor(&actors[1]);

   testQueue.insertActor(&actors[3], 42);

   auto node = testQueue.pop();
   actual[0] = node->actor->id;
   if (actual[0] != expected[0]) {
      passed = false;
   }

   node = testQueue.pop();
   actual[1] = node->actor->id;
   if (actual[1] != expected[1]) {
      passed = false;
   }
   if (node->next != 1) {
      passed = false;
      std::cout << "Node does not point to correct next index\n";
   }

   node = testQueue.pop();
   actual[2] = node->actor->id;
   if (actual[2] != expected[2]) {
      passed = false;
   }


   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, arrLength);
   }
}


void testFive(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 5: Removing effect node\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int arrLength = 3;
   int expected[] = {0,2,3};
   int actual[arrLength];

   Effect effect0 = Effect('A');
   Effect effect1 = Effect('B');
   Effect effect2 = Effect('C');
   Effect effect3 = Effect('D');
   Effect effect4 = Effect('E');

   testQueue.insertEffect(effect0, &actors[0], 42);
   testQueue.insertEffect(effect1, &actors[1], 42);
   testQueue.insertEffect(effect2, &actors[2], 42);

   testQueue.removeEffect(effect1, &actors[1]);
   testQueue.removeEffect(effect1, &actors[2]); //shouldn't remove anything

   testQueue.insertEffect(effect3, &actors[3], 42);

   auto node = testQueue.pop();
   actual[0] = node->actor->id;
   if (actual[0] != expected[0]) {
      passed = false;
   }

   node = testQueue.pop();
   actual[1] = node->actor->id;
   if (actual[1] != expected[1]) {
      passed = false;
   }
   if (node->next != 1) {
      passed = false;
      std::cout << "Node does not point to correct next index\n";
   }

   node = testQueue.pop();
   actual[2] = node->actor->id;
   if (actual[2] != expected[2]) {
      passed = false;
   }


   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, arrLength);
   }
}

void testSix(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 6: Time reset\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int turnTime = 1000000000/10;

   testQueue.insertActor(&actors[0], turnTime);

   for (int i=0; i<30; i++) {
      testQueue.insertActor(&actors[i%actors.size()], turnTime);
      printNode(testQueue.pop());
   }

   std::cout << '\n';
}


void testSeven(std::vector<ActorEntity> actors) {
   std::cout << "\nTest 7: Removing slowest actor from queue\n";

   TurnQueue testQueue = TurnQueue();
   bool passed = true;

   int arrLength = 3;
   int expected[] = {0,1,3};
   int actual[arrLength];

   testQueue.insertActor(&actors[0], 42);
   testQueue.insertActor(&actors[1], 84);
   testQueue.insertActor(&actors[2], 126);

   testQueue.removeActor(&actors[2]);

   testQueue.insertActor(&actors[3], 168);

   auto node = testQueue.pop();
   actual[0] = node->actor->id;
   if (actual[0] != expected[0]) {
      passed = false;
   }

   node = testQueue.pop();
   actual[1] = node->actor->id;
   if (actual[1] != expected[1]) {
      passed = false;
   }

   node = testQueue.pop();
   actual[2] = node->actor->id;
   if (actual[2] != expected[2]) {
      passed = false;
   }


   if (passed) {
      std::cout << "Passed\n\n";
   }
   else {
      printFailMessage(expected, actual, arrLength);
   }
}

int main() {
   std::vector<ActorEntity> actors;
   for (int i=0; i<10; i++) {
      actors.push_back(ActorEntity(i));
   }

   testOne(actors);

   testTwo(actors);

   testThree(actors);

   testFour(actors);
   
   testFive(actors);

   testSix(actors);

   testSeven(actors);
}

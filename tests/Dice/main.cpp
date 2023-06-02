#include "Randomizer.h"
#include <iostream>


int main() {
   Randomizer dice1 = Randomizer();
   Randomizer dice2 = Randomizer();
   
   std::cout << "\nTesting that the randomizers give different outputs:\n";
   for (int i=0; i<20; i++) {
      std::cout << dice1.rollD6s(1) << ' ';
   }

   std::cout << '\n';
   
   for (int i=0; i<20; i++) {
      std::cout << dice2.rollD6s(1) << ' ';
   }

   std::cout << "\n\nTesting arbitrary range function: [5,11]\n";
   
   for (int i=0; i<20; i++) {
      std::cout << dice1.getRandomNumber(11,5) << ' ';
   }

   std::cout << '\n';
}

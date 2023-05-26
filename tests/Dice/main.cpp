#include "Dice.h"
#include <iostream>


int main() {
   Dice dice1 = Dice();
   Dice dice2 = Dice();
   
   for (int i=0; i<20; i++) {
      std::cout << dice1.rollDice(1) << ' ';
   }

   std::cout << '\n';
   
   for (int i=0; i<20; i++) {
      std::cout << dice2.rollDice(1) << ' ';
   }
}

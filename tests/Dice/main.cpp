#include "Dice.h"
#include <iostream>

int main() {
   srand(time(0));

   int headsSum = 0;
   int tailsSum = 0;

   for (int i=0; i<1000000; i++) {
      if (Dice::flipCoin()) { headsSum++; }
      else { tailsSum++; }
   }

   std::cout << "\nHeads: " << headsSum;
   std::cout << "\nTails: " << tailsSum << "\n\n";


   int rolls[7];
   for (int i=0; i<1000000; i++) {
      rolls[Dice::rollDice(1)]++;
   }

   for (int i=1; i<7; i++) {
      std::cout << i << "s: " << rolls[i] << '\n';
   }

   std::cout << "\nShould be about 3500000: " << Dice::rollDice(1000000) << "\n\n";
}

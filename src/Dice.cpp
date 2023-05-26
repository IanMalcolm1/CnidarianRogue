#include "Algorithms/Dice.h"

Dice::Dice() : d6Dist(1,6) {
   std::random_device seeder;
   generator = std::mt19937(seeder());
}

bool Dice::flipCoin() {
   if ((d6Dist(generator) & 1)==1) {
      return true;
   }
   return false;
};

int Dice::rollDice(int numDice) {
   int sum = 0;

   for (int i=0; i<numDice; i++) {
      sum += d6Dist(generator);
   }

   return sum;
};

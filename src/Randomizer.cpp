#include "Algorithms/Randomizer.h"

Randomizer::Randomizer() : d6Dist(1,6) {
   std::random_device seeder;
   generator = std::mt19937(seeder());
}

bool Randomizer::flipCoin() {
   if ((d6Dist(generator) & 1)==1) {
      return true;
   }
   return false;
};

int Randomizer::rollD6s(int numDice) {
   int sum = 0;

   for (int i=0; i<numDice; i++) {
      sum += d6Dist(generator);
   }

   return sum;
};


int Randomizer::getRandomNumber(int upperLim, int lowerLim) {
   std::uniform_int_distribution<int> dist(lowerLim, upperLim);

   return dist(generator);
}

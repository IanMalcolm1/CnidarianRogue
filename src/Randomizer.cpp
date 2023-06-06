#include "Algorithms/Randomizer.h"

Randomizer::Randomizer() : coinDist(0,1) {
   std::random_device seeder;
   generator = std::mt19937(seeder());
}

bool Randomizer::flipCoin() {
   if ((coinDist(generator) & 1)==1) {
      return true;
   }
   return false;
};

int Randomizer::rollDice(int diceSize, int numDice) {
   if (diceSize < 1 || numDice < 1) {
      return 0;
   }

   std::uniform_int_distribution<int> dist(1, diceSize);

   int sum = 0;

   for (int i=0; i<numDice; i++) {
      sum += dist(generator);
   }

   return sum;
};


int Randomizer::getRandomNumber(int upperLimit) {
   std::uniform_int_distribution<int> dist(0, upperLimit);

   return dist(generator);
}

int Randomizer::getRandomNumber(int lowerLimit, int upperLimit) {
   std::uniform_int_distribution<int> dist(lowerLimit, upperLimit);

   return dist(generator);
}

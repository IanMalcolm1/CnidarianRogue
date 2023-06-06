#pragma once

#include <random>

class Randomizer {
private:
   std::uniform_int_distribution<int> coinDist;
   std::mt19937 generator;

public:
   Randomizer();

   bool flipCoin();
   int rollDice(int diceSize, int numDice);

   int getRandomNumber(int upperLimit); //returns number in range [0,upperLimit]
   int getRandomNumber(int lowerLimit, int upperLimit); //returns number in range [lowerLimit, upperLimit]
};

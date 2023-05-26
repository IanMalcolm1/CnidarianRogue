#pragma once

#include <random>

class Dice {
private:
   std::uniform_int_distribution<int> d6Dist;
   std::mt19937 generator;

public:
   Dice();

   bool flipCoin();
   int rollDice(int numDice);
};

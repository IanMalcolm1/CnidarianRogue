#pragma once

#include <random>

class Randomizer {
private:
   std::uniform_int_distribution<int> d6Dist;
   std::mt19937 generator;

public:
   Randomizer();

   bool flipCoin();
   int rollD6s(int numDice);

   //range is inclusive on both sides
   int getRandomNumber(int upperLim, int lowerLim = 0);
};

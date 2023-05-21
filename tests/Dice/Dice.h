#pragma once

#include <random>

struct Dice {
   static bool flipCoin() {
      if ((rand() & 1)==1) {
         return true;
      }
      return false;
   };

   static int rollDice(int numDice) {
      int sum = 0;

      for (int i=0; i<numDice; i++) {
         sum += rand()%6 + 1;
      }

      return sum;
   };
};

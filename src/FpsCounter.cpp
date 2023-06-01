#include "Algorithms/FpsCounter.h"
#include <chrono>


void FpsCounter::markStartPoint() {
   startPoint = std::chrono::steady_clock::now();
}

void FpsCounter::markEndPoint() {
   auto endPoint = std::chrono::steady_clock::now();
   
   std::chrono::duration<long, std::micro> diff = std::chrono::duration_cast<std::chrono::microseconds>(endPoint-startPoint);

   differences[index] = diff.count();
   index = (index+1)%differences.size();
}

int FpsCounter::getAverageFps() {
   long avgDiff = 0;
   for (long diff : differences) {
      avgDiff += diff;
   }
   avgDiff /= 8;

   return (int) (1000000/avgDiff);
}

#pragma once

#include <vector>
#include <chrono>


class FpsCounter {
private:
   int index;
   std::vector<long> differences;

   std::chrono::time_point<std::chrono::steady_clock> startPoint;


public:
   FpsCounter() : index(0), differences(8,8) {};

   void markStartPoint();
   void markEndPoint();
   int getAverageFps();
};

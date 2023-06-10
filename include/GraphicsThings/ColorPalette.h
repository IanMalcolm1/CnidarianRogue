#pragma once

#include "Algorithms/Randomizer.h"
#include "MyColor.h"
#include <vector>

class ColorPalette {
private:
	std::vector<MyColor> colors;

public:
   void addColor(MyColor color);
   void addColor(uint8_t r, uint8_t g, uint8_t b);
   MyColor getRandomColor(Randomizer* randomizer);
};

#pragma once

#include "Algorithms/Randomizer.h"
#include "Color.h"
#include <vector>

class ColorPalette {
private:
	std::vector<Color> colors;

public:
   void addColor(Color color);
   void addColor(uint8_t r, uint8_t g, uint8_t b);
   Color getRandomColor(Randomizer* randomizer);
};

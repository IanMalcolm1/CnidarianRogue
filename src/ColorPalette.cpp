#include "GraphicsThings/ColorPalette.h"


void ColorPalette::addColor(Color color) {
   colors.push_back(color);
}

void ColorPalette::addColor(uint8_t r, uint8_t g, uint8_t b) {
   colors.push_back(Color(r,g,b));
}

Color ColorPalette::getRandomColor(Randomizer* randomizer) {
   return colors[randomizer->getRandomNumber(colors.size()-1)];
}

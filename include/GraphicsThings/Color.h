#pragma once

#include <cstdint>
#include <string>

//Unsigned 8-bit integers for red, green, and blue
struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	Color(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {};

	void set(uint8_t red, uint8_t green, uint8_t blue);
   std::string getString();

   bool operator == (const Color color) const {
      return r==color.r && g==color.g && b==color.b;
   }
};

#pragma once

#include <cstdint>

//Unsigned 8-bit integers for red, green, and blue
struct MyColor {
	uint8_t r;
	uint8_t g;
	uint8_t b;

	MyColor(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {};

	void set(uint8_t red, uint8_t green, uint8_t blue);
};

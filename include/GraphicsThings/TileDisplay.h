#pragma once

#include "Enums/AsciiSymbols.h"
#include "MyColor.h"

//Display info for tiles. Meant to take up minimal space possible.
struct TileDisplay {
	uint8_t symbol;
	MyColor symbolColor;
	MyColor backColor;

	TileDisplay(uint8_t symbol = ASYM_SMILE_THIN, MyColor symbolColor = MyColor(255, 255, 255),
		MyColor backColor = MyColor()) : symbol(symbol), symbolColor(symbolColor),
		backColor(backColor) {};

	void copy(TileDisplay* display);
};

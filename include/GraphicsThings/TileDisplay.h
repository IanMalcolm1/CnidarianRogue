#pragma once

#include "Enums/AsciiSymbols.h"
#include "Color.h"


struct EntityDisplay {
	uint8_t symbol;
	Color symbolColor;

	EntityDisplay(uint8_t symbol = ASYM_SMILE_THIN, Color symbolColor = Color(255, 255, 255)) :
   symbol(symbol), symbolColor(symbolColor) {};
};


struct TileDisplay {
	uint8_t symbol;
	Color symbolColor;
	Color backColor;

	TileDisplay(uint8_t symbol = ASYM_SMILE_THIN, Color symbolColor = Color(255, 255, 255),
	Color backColor = Color()) : symbol(symbol), symbolColor(symbolColor), backColor(backColor) {};

   TileDisplay(EntityDisplay entityDisplay, Color backColor) : symbol(entityDisplay.symbol),
   symbolColor(entityDisplay.symbolColor), backColor(backColor) {};

	bool operator == (const TileDisplay display) const {
      return symbol==display.symbol && symbolColor==display.symbolColor && backColor==display.backColor;
	}
};

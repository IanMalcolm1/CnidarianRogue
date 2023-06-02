#pragma once

#include "Enums/AsciiSymbols.h"
#include "MyColor.h"


struct EntityDisplay {
	uint8_t symbol;
	MyColor symbolColor;

	EntityDisplay(uint8_t symbol = ASYM_SMILE_THIN, MyColor symbolColor = MyColor(255, 255, 255)) :
   symbol(symbol), symbolColor(symbolColor) {};
};


struct TileDisplay {
	uint8_t symbol;
	MyColor symbolColor;
	MyColor backColor;

	TileDisplay(uint8_t symbol = ASYM_SMILE_THIN, MyColor symbolColor = MyColor(255, 255, 255),
	MyColor backColor = MyColor()) : symbol(symbol), symbolColor(symbolColor), backColor(backColor) {};

   TileDisplay(EntityDisplay entityDisplay, MyColor backColor) : symbol(entityDisplay.symbol),
   symbolColor(entityDisplay.symbolColor), backColor(backColor) {};

	bool operator == (const TileDisplay display) const {
      return symbol==display.symbol && symbolColor==display.symbolColor && backColor==display.backColor;
	}
};

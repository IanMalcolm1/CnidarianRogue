#include "GraphicsThings/MyColor.h"
#include "GraphicsThings/TileDisplay.h"
#include "GraphicsThings/ColorMap.h"
#include "Logs/DebugLogger.h"
#include <stdexcept>

/* MyColor */

void MyColor::set(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
}


/* TileDisplay */

void TileDisplay::copy(TileDisplay* display) {
	symbol = display->symbol;
	symbolColor = display->symbolColor;
	backColor = display->backColor;
}


/* ColorMap */

ColorMap::ColorMap() {
	initializeColorMap();
}

void ColorMap::initializeColorMap() {
	colorMap.insert({ "red", MyColor(255, 0, 0) });
	colorMap.insert({ "orange", MyColor(255,165,0) });
	colorMap.insert({ "yellow", MyColor(255,255,0) });
	colorMap.insert({ "gold", MyColor(255,215,0) });

	colorMap.insert({ "green", MyColor(0, 255, 0) });
	colorMap.insert({ "lightgreen", MyColor(144, 238, 144) });

	colorMap.insert({ "blue", MyColor(0, 0, 255) });
	colorMap.insert({ "lightblue", MyColor(173, 216, 230) });

	colorMap.insert({ "purple", MyColor(160, 32, 240) });
	colorMap.insert({ "pink", MyColor(255,192,203) });

	colorMap.insert({ "pink", MyColor(165, 42, 42) });
}

MyColor ColorMap::getColorByName(std::string name) {
	try {
		return colorMap[name];
	}
	catch (std::out_of_range e) {
      DebugLogger::log("Game message format error: Color name '" + name + "' is unrecognized");
		return MyColor(255, 255, 255);
	}
}

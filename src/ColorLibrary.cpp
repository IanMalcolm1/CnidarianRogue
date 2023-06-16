#include "GraphicsThings/ColorLibrary.h"
#include "Logs/DebugLogger.h"
#include <stdexcept>

ColorLibrary::ColorLibrary() {
	initialize();
}

void ColorLibrary::initialize() {
	colorMap.insert({ "red", Color(255, 0, 0) });
	colorMap.insert({ "darkred", Color(165, 42, 42) });
	colorMap.insert({ "maroon", Color(128, 0, 0) });

	colorMap.insert({ "orange", Color(255,165,0) });
   colorMap.insert({ "brown", Color(150, 75, 0) });

	colorMap.insert({ "yellow", Color(255,255,0) });
	colorMap.insert({ "gold", Color(255,215,0) });
	colorMap.insert({ "darkgold", Color(181,148,16) });

	colorMap.insert({ "green", Color(0, 255, 0) });
	colorMap.insert({ "lightgreen", Color(144, 238, 144) });

	colorMap.insert({ "blue", Color(0, 0, 255) });
	colorMap.insert({ "lightblue", Color(173, 216, 230) });

	colorMap.insert({ "purple", Color(160, 32, 240) });
   colorMap.insert({ "lavender", Color(220, 208, 255) });
	colorMap.insert({ "pink", Color(255,192,203) });

   colorMap.insert({ "grey", Color(128,128,128) });
   colorMap.insert({ "lightgrey", Color(192,192,192) });
   colorMap.insert({ "darkgrey", Color(64,64,64) });
   colorMap.insert({ "slategrey", Color(119,136,153) });
}

Color ColorLibrary::getColor(std::string name) {
	try {
		return colorMap[name];
	}
	catch (std::out_of_range e) {
      DebugLogger::log("Game message format error: Color name '" + name + "' is unrecognized");
		return Color(255, 255, 255);
	}
}

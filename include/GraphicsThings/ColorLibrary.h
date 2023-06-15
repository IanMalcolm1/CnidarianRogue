#pragma once

#include <unordered_map>
#include <string>
#include "GraphicsThings/Color.h"

class ColorLibrary {
private:
	std::unordered_map<std::string, Color> colorMap;
	void initialize();

public:
	ColorLibrary();

	Color getColor(std::string name);
};

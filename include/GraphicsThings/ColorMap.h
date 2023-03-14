#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include "Logs/DebugLogger.h"
#include "MyColor.h"

class ColorMap {
private:
	std::unique_ptr<DebugLogger> debugLogger;

	std::unordered_map<std::string, MyColor> colorMap;
	void initializeColorMap();

public:
	ColorMap();

	MyColor getColorByName(std::string name);
};

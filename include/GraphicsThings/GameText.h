#pragma once

#include <vector>
#include <string>
#include "ColorMap.h"
#include "Logs/DebugLogger.h"


struct GameTextColorNode {
	MyColor color;
	uint16_t endIndex;

	GameTextColorNode() : color({ 0,0,0 }), endIndex(0) {};
	GameTextColorNode(MyColor color, uint16_t endIndex) : color(color), endIndex(endIndex) {};
};


class GameText {
private:
	std::vector<GameTextColorNode> colorNodes;
	std::string text;

public:
	GameText() : colorNodes(NULL), text("") {};
	GameText(std::string text, std::vector<GameTextColorNode> colorNodes) : text(text),
		colorNodes(colorNodes) {};

	MyColor getColorAtIndex(int index);
	std::string getText();
};


class GameTextMaker {
	std::unique_ptr<ColorMap> colorMap;
	std::unique_ptr<DebugLogger> debugLogger;

	MyColor readColor(int& index, std::string& text);
	MyColor readColorByRGB(int& index, std::string& text);
	int readColorRGBValue(int& index, std::string& text);
	MyColor readColorByColorName(int& index, std::string& text);

public:
	GameTextMaker();

	/*
	By default text is white.

	To start a colored section of text, use </colorName: or </rrrgggbbb:
	Examples: </red: or </255000000:

	To end a colored section of text, use />
	*/
	GameText makeGameText(std::string rawText);
};

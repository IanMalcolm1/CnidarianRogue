#pragma once

#include <vector>
#include <string>
#include "ColorMap.h"


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
	GameText() : colorNodes(std::vector<GameTextColorNode>()), text("") {};
	GameText(std::string text, std::vector<GameTextColorNode> colorNodes) : text(text),
		colorNodes(colorNodes) {};

	MyColor getColorAtIndex(int index);
	std::string getText();
};


class GameTextMaker {
	std::unique_ptr<ColorMap> colorMap;

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

   Example: "Hi, I'm </000255000:Ian/>. Te</000255000:eeeeeeeee/>est. Another </red:test/>. Now I have more </lightblue:colors/>!"
	*/
	GameText makeGameText(std::string rawText);
};

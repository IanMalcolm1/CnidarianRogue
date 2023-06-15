#pragma once

#include "GraphicsThings/GameText.h"
#include "ColorLibrary.h"


class GameTextMaker {
   ColorLibrary colorMap;

	Color readColor(int& index, std::string& text);
	Color readColorByRGB(int& index, std::string& text);
	int readColorRGBValue(int& index, std::string& text);
	Color readColorByColorName(int& index, std::string& text);

public:
	GameTextMaker() : colorMap() {};

	/*
	By default text is white.

	To start a colored section of text, use </colorName: or </rrrgggbbb:
	Examples: </red: or </255000000:

	To end a colored section of text, use \\>

   Example: "Hi, I'm </000255000:Ian\\>. Te</000255000:eeeeeeeee\\>est. Another </red:test\\>. Now I have more </lightblue:colors\\>!"
	*/
	GameText makeGameText(std::string rawText);
};

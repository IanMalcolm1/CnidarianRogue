#pragma once

#include "GraphicsThings/MyColor.h"
#include <vector>
#include <string>
#include <cstdint>


struct TextColorNode {
	MyColor color;
	uint16_t endIndex;

	TextColorNode() : color({ 0,0,0 }), endIndex(0) {};
	TextColorNode(MyColor color, uint16_t endIndex) : color(color), endIndex(endIndex) {};
};

class TextColorMap {
private:
	std::vector<TextColorNode> nodes;

public:
   void addColorNode(MyColor color, int endIndex);
	MyColor getColorAtIndex(int index);
   bool empty();
   int lastIndex();
};


class GameText {
private:
   TextColorMap colorMap;
	std::string text;

public:
	GameText() : text(), colorMap() {};
	GameText(std::string text, TextColorMap colorMap) : text(text),
	colorMap(colorMap) {};

	MyColor getColorAtIndex(int index);
	std::string getText();
   TextColorMap getColorMap();
};


class FormattedText {
private:
   std::string text;
   TextColorMap colorMap;
   int height;

public:
   FormattedText() : height(0) {};
   FormattedText(std::string text, int height, TextColorMap colorMap) :
   text(text), height(height), colorMap(colorMap) {};

   int textSize();
   uint8_t charAt(int index);
   int getHeight();
	MyColor getColorAtIndex(int index);
};

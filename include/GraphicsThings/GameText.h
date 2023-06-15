#pragma once

#include "GraphicsThings/Color.h"
#include <vector>
#include <string>
#include <cstdint>


struct TextColorNode {
	Color color;
	uint16_t endIndex;

	TextColorNode() : color({ 0,0,0 }), endIndex(0) {};
	TextColorNode(Color color, uint16_t endIndex) : color(color), endIndex(endIndex) {};
};

class TextColorMap {
private:
	std::vector<TextColorNode> nodes;

public:
   void addColorNode(Color color, int endIndex);
	Color getColorAtIndex(int index);
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

	Color getColorAtIndex(int index);
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
	Color getColorAtIndex(int index);
};

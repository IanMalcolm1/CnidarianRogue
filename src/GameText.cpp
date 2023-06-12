#include "GraphicsThings/GameText.h"
#include "Logs/DebugLogger.h"


void TextColorMap::addColorNode(MyColor color, int endIndex) {
   nodes.push_back(TextColorNode(color, endIndex));
}

MyColor TextColorMap::getColorAtIndex(int index) {
	for (TextColorNode node : nodes) {
		if (index <= node.endIndex) {
			return node.color;
		}
	}


   DebugLogger::log("Message display error: Reached end of color nodes");
	return MyColor(255, 255, 255);
}

bool TextColorMap::empty() { return nodes.size()==0; }

int TextColorMap::lastIndex() {
   return nodes.back().endIndex;
}


/* Game Text */

MyColor GameText::getColorAtIndex(int index) {
   return colorMap.getColorAtIndex(index);
}

std::string GameText::getText() { return text; }

TextColorMap GameText::getColorMap() { return colorMap; }


/* Formatted Text */

int FormattedText::textSize() {
   return text.size();
}

uint8_t FormattedText::charAt(int index) { return text[index]; }

int FormattedText::getHeight() { return height; };

MyColor FormattedText::getColorAtIndex(int index) {
   return colorMap.getColorAtIndex(index);
}

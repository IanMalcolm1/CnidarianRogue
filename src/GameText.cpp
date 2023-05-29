#include "GraphicsThings/GameText.h"
#include "Logs/DebugLogger.h"
#include <stack>


/* Game Text */

MyColor GameText::getColorAtIndex(int index) {
	for (GameTextColorNode node : colorNodes) {
		if (index <= node.endIndex) {
			return node.color;
		}
	}


	printf("Message display error: Reached end of color nodes");
	return MyColor(255, 255, 255);
}

std::string GameText::getText() { return text; }


/* Game Text Maker */

GameText GameTextMaker::makeGameText(std::string rawText) {
	std::vector<GameTextColorNode> colorNodes;

	std::stack<MyColor> colorStack;
	colorStack.push(MyColor(255, 255, 255));

	std::string newText;
	int newTextIndex = -1;

	for (int i = 0; i < rawText.size(); i++) {
		if (rawText[i] == '<' && rawText[i + 1] == '/') {
			if (newTextIndex != -1) {
				colorNodes.push_back(GameTextColorNode(colorStack.top(), newTextIndex));
			}

			colorStack.push(readColor(i, rawText));
		}

		else if (rawText[i] == '/' && rawText[i + 1] == '>') {
			colorNodes.push_back(GameTextColorNode(colorStack.top(), newTextIndex));
			colorStack.pop();

			i++;
		}

		else {
			newText.push_back(rawText[i]);
			newTextIndex++;
		}
	}

	//the final color, if it's needed
	if (colorNodes.size() > 0) {
		if (colorNodes.back().endIndex != newTextIndex) {
			colorNodes.push_back(GameTextColorNode(colorStack.top(), newTextIndex));
		}
	}
	else {
		colorNodes.push_back(GameTextColorNode(colorStack.top(), newTextIndex));
	}

	return GameText(newText, colorNodes);
}

int GameTextMaker::readColorRGBValue(int& index, std::string& text) {
	std::string value;

	for (int counter = 0; counter < 3; counter++) {
		if (index >= text.size()) {
			DebugLogger::log("Game message format error: Reading RGB values exceeded length of string\n" + text);
			return 0;
		}
		else {
			value.push_back(text[index]);
			index++;
		}
	}
	return std::stoi(value);
}


MyColor GameTextMaker::readColorByRGB(int& index, std::string& text) {
	MyColor color;

	color.r = readColorRGBValue(index, text);
	color.g = readColorRGBValue(index, text);
	color.b = readColorRGBValue(index, text);

	return color;
}

MyColor GameTextMaker::readColorByColorName(int& index, std::string& text) {
	std::string colorName;

	while (index < text.size()) {
		if (text[index] == ':') {
			return colorMap.getColor(colorName);
		}
		else {
			colorName.push_back(text[index]);
		}

		index++;
	}

	DebugLogger::log("Game message format error: End of string reached while trying to parse color name\n" + text);
	return MyColor(255, 255, 255);
}


MyColor GameTextMaker::readColor(int& index, std::string& text) {
	index += 2;

	if (text[index] >= '0' && text[index] <= '9') {
		return readColorByRGB(index, text);
	}

	else {
		return readColorByColorName(index, text);
	}
}

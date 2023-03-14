#include "UIScreens/TextRenderer.h"
#include "Enums/AsciiSymbols.h"


void TextRenderer::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

std::pair<std::string, int> TextRenderer::formatGameText(TextRenderingSpecs& specs, GameText& gameText) {
	int lines = 1;
	int index = specs.maxLettersPerLine - 1;

	std::string text = gameText.getText();

	while (index < (int)text.size()) {

		if (text[index] == ASYM_SPACE) {
			text[index] = '\n';
			lines++;
		}

		else if (text[index + 1] == ASYM_SPACE) {
			index++;
			text[index] = '\n';
			lines++;
		}

		else {
			int prevIndex = index;
			while (index > 0) {
				index--;
				if (text[index] == ASYM_SPACE) {
					text.insert(text.begin() + index + 1, '\n');
					index+=2;
					lines++;
					break;
				}
				else if (prevIndex - index == specs.maxLettersPerLine) {
					text.insert(text.begin() + prevIndex + 1, '\n');
					lines++;
					index = prevIndex + 1;
					break;
				}
			}
			if (index == 0) {
				text.insert(text.begin() + prevIndex + 1, '\n');
				lines++;
				index = prevIndex + 1;
			}
		}

		index += specs.maxLettersPerLine;
	}

	int height = lines * specs.fontSizePixels + (lines - 1) * specs.lineSpacing;

	return std::make_pair(text, height);
}


int TextRenderer::renderGameTextDown(TextRenderingSpecs& specs, GameText& gameText, int startY) {
	std::pair<std::string, int> formattedText;
	formattedText = formatGameText(specs, gameText);

	int height = formattedText.second;

	if (startY + height < 0) {
		return startY + height;
	}

	renderFormattedText(specs, formattedText.first, gameText, startY);

	return startY+height;
}


int TextRenderer::renderGameTextUp(TextRenderingSpecs& specs, GameText& gameText, int startY) {
	std::pair<std::string, int> formattedText;
	formattedText = formatGameText(specs, gameText);

	if (startY < 0) {
		return startY - formattedText.second;
	}

	startY -= formattedText.second;

	renderFormattedText(specs, formattedText.first, gameText, startY);

	return startY;
}

int TextRenderer::renderFormattedTextDown(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY) {
	int height = fText.second;

	if (startY + height < 0) {
		return startY + height;
	}

	renderFormattedText(specs, fText.first, gameText, startY);

	return startY + height;
}

int TextRenderer::renderFormattedTextUp(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY) {
	if (startY < 0) {
		return startY - fText.second;
	}

	startY -= fText.second;

	renderFormattedText(specs, fText.first, gameText, startY);

	return startY;
}


void TextRenderer::renderFormattedText(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY) {
	SDL_Rect sourceRect = { 0,0,8,8 };
	SDL_Rect destinationRect = { specs.margin, startY, specs.fontSizePixels, specs.fontSizePixels };

	int unformattedIndex = 0;
	MyColor currentColor;

	char currChar;

	for (int i = 0; i < fText.size(); i++) {
		currChar = fText[i];

		if (currChar == '\n') {
			destinationRect.y += specs.fontSizePixels + specs.lineSpacing;
			destinationRect.x = specs.margin;
			continue;
		}

		sourceRect.x = currChar % 16 * 8;
		sourceRect.y = currChar / 16 * 8;

		currentColor = gameText.getColorAtIndex(unformattedIndex);

		SDL_SetTextureColorMod(spritesheet, currentColor.r, currentColor.g, currentColor.b);
		SDL_RenderCopy(renderer, spritesheet, &sourceRect, &destinationRect);

		destinationRect.x += specs.fontSizePixels;

		unformattedIndex++;
	}
}



void TextRenderingSpecs::modifyFontSize(int modification) {
	int temporary = fontSize + modification;

	if (temporary < 1 || temporary > 10) {
		return;
	}

	fontSize += modification;
	fontSizePixels = 8 * fontSize;
	lineSpacing = fontSizePixels / 4;
	messageSpacing = fontSizePixels / 2;
}

void TextRenderingSpecs::calcMaxLettersPerLine(int viewportWidth) {
	maxLettersPerLine = (viewportWidth - 2 * margin) / fontSizePixels;
}

#include "GraphicsThings/TextRenderer.h"
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


int TextRenderer::renderGameText(TextRenderingSpecs& specs, GameText& gameText, int startY, int options) {
	std::pair<std::string, int> formattedText;
	formattedText = formatGameText(specs, gameText);
   
   if ((options & TEXT_RENDER_DOWN) == TEXT_RENDER_DOWN) {
      return renderFormattedTextDown(specs, formattedText, gameText, startY, options);
   }
   else {
      return renderFormattedTextUp(specs, formattedText, gameText, startY, options);
   }
}

int TextRenderer::renderFormattedText(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
   if ((options & TEXT_RENDER_DOWN) == TEXT_RENDER_DOWN) {
      return renderFormattedTextDown(specs, fText, gameText, startY, options);
   }
   else {
      return renderFormattedTextUp(specs, fText, gameText, startY, options);
   }
}


int TextRenderer::renderFormattedTextDown(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
	int height = fText.second;

	if (startY + height < 0) {
		return startY + height;
	}

   if ((options & TEXT_ALIGN_LEFT) == TEXT_ALIGN_LEFT) {
      renderTextLeftAligned(specs, fText.first, gameText, startY);
   }
   else {
      renderTextCentered(specs, fText.first, gameText, startY);
   }

	return startY + height;
}

int TextRenderer::renderFormattedTextUp(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
	if (startY < 0) {
		return startY - fText.second;
	}

	startY -= fText.second;

   if ((options & TEXT_ALIGN_LEFT) == TEXT_ALIGN_LEFT) {
      renderTextLeftAligned(specs, fText.first, gameText, startY);
   }
   else {
      renderTextCentered(specs, fText.first, gameText, startY);
   }

	return startY;
}


void TextRenderer::renderTextLeftAligned(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY) {
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


void TextRenderer::renderTextCentered(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY) {
	SDL_Rect sourceRect = { 0,0,8,8 };
	SDL_Rect destinationRect = { 0, startY, specs.fontSizePixels, specs.fontSizePixels };

   destinationRect.x = (specs.viewportWidth - calcLineLength(specs, fText, -1))/2;

	int unformattedIndex = 0;
	MyColor currentColor;

	char currChar;

	for (int i = 0; i < fText.size(); i++) {
		currChar = fText[i];

		if (currChar == '\n') {
			destinationRect.y += specs.fontSizePixels + specs.lineSpacing;
         destinationRect.x = (specs.viewportWidth - calcLineLength(specs, fText, i))/2;
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


int TextRenderer::calcLineLength(TextRenderingSpecs& specs,std::string& text, int startIndex) {
   int length = 0;
   for (int i=startIndex+1; i<text.length(); i++) {
      if (text[i] == '\n') {
         return length;
      }
      length += specs.fontSizePixels;
   }
   return length;
}


void TextRenderingSpecs::modifyFontSize(int modification) {
	int newFontSize = fontSize + modification;

	if (newFontSize < 1 || newFontSize > 10) {
		return;
	}

	fontSize = newFontSize;
	fontSizePixels = 8 * newFontSize;
	lineSpacing = fontSizePixels / 4;
	messageSpacing = fontSizePixels / 2;
}

void TextRenderingSpecs::setViewportWidth(int viewportWidth) {
   this->viewportWidth = viewportWidth;
	maxLettersPerLine = (viewportWidth - 2 * margin) / fontSizePixels;
}

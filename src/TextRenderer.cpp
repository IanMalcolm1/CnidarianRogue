#include "GraphicsThings/TextRenderer.h"
#include "Enums/AsciiSymbols.h"
#include "GraphicsThings/GameText.h"
#include <cstdint>


void TextRenderer::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

std::pair<std::string, int> TextRenderer::formatGameText(TextRenderingSpecs& specs, GameText& gameText) {
	int height = specs.fontSizePixels;
	std::string text = gameText.getText();


   int lastNewline = -1;
   for (int i=0; i<text.size(); i++) {
      if (text[i] == '\n') {
         lastNewline = i;
         height += specs.fontSizePixels + specs.messageSpacing;
         continue;
      }
      if (i-lastNewline < specs.maxLettersPerLine+1) {
         continue;
      }

		if (text[i] == ' ') {
			text.insert(text.begin() + i + 1, '\r');
         lastNewline = i = i+1;
			height += specs.fontSizePixels + specs.lineSpacing;
		}

		else if (i+1<text.size() && text[i + 1] == ' ') {
			text.insert(text.begin() + i + 1, '\r');
         lastNewline = i = i+1;
			height += specs.fontSizePixels + specs.lineSpacing;
		}

		else {
         int j = i;
			while (j > 0) {
				j--;
				if (text[j] == ' ') {
					text.insert(text.begin() + j + 1, '\r');
               lastNewline = i = j+1;
					height += specs.fontSizePixels + specs.lineSpacing;
					break;
				}
				else if (i - j == specs.maxLettersPerLine) {
					text.insert(text.begin() + i, '\r');
               lastNewline = i;
					height += specs.fontSizePixels + specs.lineSpacing;
					break;
				}
			}
			if (j == -1) {
				text.insert(text.begin() + i, '\r');
            lastNewline = i;
            i--;
				height += specs.fontSizePixels + specs.lineSpacing;
			}
		}
   }


	return std::make_pair(text, height);
}


int TextRenderer::renderGameText(TextRenderingSpecs& specs, GameText& gameText, int startY, int options) {
	std::pair<std::string, int> formattedText;
	formattedText = formatGameText(specs, gameText);
   
   if ((options & TEXT_RENDER_UP) == TEXT_RENDER_UP) {
      return renderFormattedTextUp(specs, formattedText, gameText, startY, options);
   }
   else {
      return renderFormattedTextDown(specs, formattedText, gameText, startY, options);
   }
}

int TextRenderer::renderFormattedText(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
   if ((options & TEXT_RENDER_UP) == TEXT_RENDER_UP) {
      return renderFormattedTextUp(specs, fText, gameText, startY, options);
   }
   else {
      return renderFormattedTextDown(specs, fText, gameText, startY, options);
   }
}


int TextRenderer::renderFormattedTextDown(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
	int height = fText.second;

	if (startY + height < 0) {
		return startY + height;
	}

   if ((options & TEXT_ALIGN_CENTER) == TEXT_ALIGN_CENTER) {
      renderTextCentered(specs, fText.first, gameText, startY);
   }
   else {
      renderTextLeftAligned(specs, fText.first, gameText, startY);
   }

	return startY + height;
}

int TextRenderer::renderFormattedTextUp(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY, int options) {
	if (startY < 0) {
		return startY - fText.second;
	}

	startY -= fText.second;

   if ((options & TEXT_ALIGN_CENTER) == TEXT_ALIGN_CENTER) {
      renderTextCentered(specs, fText.first, gameText, startY);
   }
   else {
      renderTextLeftAligned(specs, fText.first, gameText, startY);
   }

	return startY;
}


void TextRenderer::renderTextLeftAligned(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY) {
	SDL_Rect sourceRect = { 0,0,8,8 };
	SDL_Rect destinationRect = { specs.margin, startY, specs.fontSizePixels, specs.fontSizePixels };

	int unformattedIndex = 0;
	MyColor currentColor;

	uint8_t currChar;

	for (int i = 0; i < fText.size(); i++) {
		currChar = fText[i];

		if (currChar == '\n') {
			destinationRect.y += specs.fontSizePixels + specs.messageSpacing;
			destinationRect.x = specs.margin;
         unformattedIndex++;
         continue;
		}
      if (currChar == '\r') {
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

	uint8_t currChar;

	for (int i = 0; i < fText.size(); i++) {
		currChar = fText[i];

		if (currChar == '\n') {
			destinationRect.y += specs.fontSizePixels + specs.messageSpacing;
         destinationRect.x = (specs.viewportWidth - calcLineLength(specs, fText, i))/2;
         unformattedIndex++;
			continue;
		}
		if (currChar == '\r') {
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




int TextRenderer::renderLineSeparator(TextRenderingSpecs& specs, GameTextMaker& textMaker, int startY) {
   std::string line = "";
   for (int i=0; i<specs.maxLettersPerLine - 1; i++) {
      line.append("-");
   }

   GameText lineText = textMaker.makeGameText(line);
   renderGameText(specs, lineText, startY + specs.lineSpacing, TEXT_ALIGN_CENTER);
   
   return startY + specs.fontSizePixels + 2*specs.lineSpacing;
}


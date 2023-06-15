#include "GraphicsThings/TextRenderer.h"
#include "Enums/AsciiSymbols.h"
#include "GraphicsThings/GameText.h"
#include <cstdint>


void TextRenderer::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;
}

FormattedText TextRenderer::formatGameText(TextRenderingSpecs& specs, GameText& gameText) {
	int fHeight = specs.fontSizePixels;
   std::string fText = gameText.getText();


   int lastNewline = -1;
   for (int i=0; i<fText.size(); i++) {
      if (fText[i] == '\n') {
         lastNewline = i;
         fHeight += specs.fontSizePixels + specs.messageSpacing;
         continue;
      }
      if (i-lastNewline < specs.maxLettersPerLine+1) {
         continue;
      }

		if (fText[i] == ' ') {
			fText.insert(fText.begin() + i + 1, '\r');
         lastNewline = i = i+1;
			fHeight += specs.fontSizePixels + specs.lineSpacing;
		}

		else if (i+1<fText.size() && fText[i + 1] == ' ') {
			fText.insert(fText.begin() + i + 1, '\r');
         lastNewline = i = i+1;
			fHeight += specs.fontSizePixels + specs.lineSpacing;
		}

		else {
         int j = i;
			while (j > 0) {
				j--;
				if (fText[j] == ' ') {
					fText.insert(fText.begin() + j + 1, '\r');
               lastNewline = i = j+1;
					fHeight += specs.fontSizePixels + specs.lineSpacing;
					break;
				}
				else if (i - j == specs.maxLettersPerLine) {
					fText.insert(fText.begin() + i, '\r');
               lastNewline = i;
					fHeight += specs.fontSizePixels + specs.lineSpacing;
					break;
				}
			}
			if (j == -1) {
				fText.insert(fText.begin() + i, '\r');
            lastNewline = i;
            i--;
				fHeight += specs.fontSizePixels + specs.lineSpacing;
			}
		}
   }


	return FormattedText(fText, fHeight, gameText.getColorMap());
}


int TextRenderer::renderGameText(TextRenderingSpecs& specs, GameText& gameText, int startY, int options) {
	FormattedText ftext = formatGameText(specs, gameText);
   
   if ((options & TEXT_RENDER_UP) == TEXT_RENDER_UP) {
      return renderFormattedTextUp(specs, ftext, startY, options);
   }
   else {
      return renderFormattedTextDown(specs, ftext, startY, options);
   }
}

int TextRenderer::renderFormattedText(TextRenderingSpecs& specs, FormattedText& fText, int startY, int options) {
   if ((options & TEXT_RENDER_UP) == TEXT_RENDER_UP) {
      return renderFormattedTextUp(specs, fText, startY, options);
   }
   else {
      return renderFormattedTextDown(specs, fText, startY, options);
   }
}


int TextRenderer::renderFormattedTextDown(TextRenderingSpecs& specs, FormattedText& fText, int startY, int options) {
	int height = fText.getHeight();

	if (startY + height < 0) {
		return startY + height;
	}

   if ((options & TEXT_ALIGN_CENTER) == TEXT_ALIGN_CENTER) {
      renderTextCentered(specs, fText, startY);
   }
   else {
      renderTextLeftAligned(specs, fText, startY);
   }

	return startY + height;
}

int TextRenderer::renderFormattedTextUp(TextRenderingSpecs& specs, FormattedText& fText, int startY, int options) {
	if (startY < 0) {
		return startY - fText.getHeight();
	}

	startY -= fText.getHeight();

   if ((options & TEXT_ALIGN_CENTER) == TEXT_ALIGN_CENTER) {
      renderTextCentered(specs, fText, startY);
   }
   else {
      renderTextLeftAligned(specs, fText, startY);
   }

	return startY;
}


void TextRenderer::renderTextLeftAligned(TextRenderingSpecs& specs, FormattedText& fText, int startY) {
	SDL_Rect sourceRect = { 0,0,8,8 };
	SDL_Rect destinationRect = { specs.margin, startY, specs.fontSizePixels, specs.fontSizePixels };

	int unformattedIndex = 0;
	Color currentColor;

	uint8_t currChar;

	for (int i = 0; i < fText.textSize(); i++) {
		currChar = fText.charAt(i);

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

		currentColor = fText.getColorAtIndex(unformattedIndex);

		SDL_SetTextureColorMod(spritesheet, currentColor.r, currentColor.g, currentColor.b);
		SDL_RenderCopy(renderer, spritesheet, &sourceRect, &destinationRect);

		destinationRect.x += specs.fontSizePixels;

		unformattedIndex++;
	}
}


void TextRenderer::renderTextCentered(TextRenderingSpecs& specs, FormattedText& fText, int startY) {
	SDL_Rect sourceRect = { 0,0,8,8 };
	SDL_Rect destinationRect = { 0, startY, specs.fontSizePixels, specs.fontSizePixels };

   destinationRect.x = (specs.viewportWidth - calcLineLength(specs, fText, -1))/2;

	int unformattedIndex = 0;
	Color currentColor;

	uint8_t currChar;

	for (int i = 0; i < fText.textSize(); i++) {
		currChar = fText.charAt(i);

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

		currentColor = fText.getColorAtIndex(unformattedIndex);

		SDL_SetTextureColorMod(spritesheet, currentColor.r, currentColor.g, currentColor.b);
		SDL_RenderCopy(renderer, spritesheet, &sourceRect, &destinationRect);

		destinationRect.x += specs.fontSizePixels;

		unformattedIndex++;
	}
}


int TextRenderer::calcLineLength(TextRenderingSpecs& specs, FormattedText& fText, int startIndex) {
   int length = 0;
   for (int i=startIndex+1; i<fText.textSize(); i++) {
      if (fText.charAt(i) == '\n') {
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


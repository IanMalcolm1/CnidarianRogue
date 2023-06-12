#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "GraphicsThings/GameText.h"


struct TextRenderingSpecs {
	int fontSize, fontSizePixels;
	int margin, lineSpacing, messageSpacing;
	int viewportWidth, maxLettersPerLine;
	int startOffset;

	TextRenderingSpecs(int fontSize = 2, int margin = 16) : fontSize(fontSize),
		fontSizePixels(8 * fontSize), margin(margin), lineSpacing(fontSizePixels / 4),
		messageSpacing(fontSizePixels / 2), startOffset(-margin), maxLettersPerLine(0) {};

	void modifyFontSize(int modification);
	void setViewportWidth(int viewportWidth);
};


enum TextRenderingOptions {
   TEXT_ALIGN_LEFT = 0b1,
   TEXT_ALIGN_CENTER = 0b10,
   TEXT_RENDER_DOWN = 0b100, //Render down starting from startY
   TEXT_RENDER_UP = 0b1000 //Render up starting from startY
};


struct FormattedText {
   std::string text;
   GameText gameText;
   TextRenderingSpecs specs;
   int height;
};


class TextRenderer {
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	void renderTextLeftAligned(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY);
   void renderTextCentered(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY);

	int renderFormattedTextDown(TextRenderingSpecs& specs, FormattedText& fText, GameText& gameText, int startY, int options);
	int renderFormattedTextUp(TextRenderingSpecs& specs, FormattedText& fText, GameText& gameText, int startY, int options);

   //Start index should be -1 for the first line
   int calcLineLength(TextRenderingSpecs& specs,std::string& text, int startIndex);


public:
	TextRenderer() : renderer(NULL), spritesheet(NULL) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spriteSheet);

   /* Renders a GameText object to the screen.
    * Takes a bitmask of TextRenderingOptions in options argument.
    * Returns ending y coordinate. */
	int renderGameText(TextRenderingSpecs& specs, GameText& gameText, int startY, int options = (TEXT_ALIGN_LEFT | TEXT_RENDER_DOWN));

   /* Renders a formatted GameText object (a string and a height).
    * Takes a bitmask of TextRenderingOptions in options argument.
    * Returns ending y coordinate. */
	int renderFormattedText(TextRenderingSpecs& specs, FormattedText& fText, GameText& gameText, int startY, int options = (TEXT_ALIGN_LEFT | TEXT_RENDER_DOWN));


   int renderLineSeparator(TextRenderingSpecs& specs, GameTextMaker& textMaker, int startY);


   /* Adds newline characters as necessary to keep text from exceeding
    * specs.maxLettersPerLine. Returns modified string with the calculated
    * height of the message. */
	FormattedText formatGameText(TextRenderingSpecs& specs, GameText& gameText);
};

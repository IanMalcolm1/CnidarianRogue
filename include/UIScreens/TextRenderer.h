#pragma once

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "GraphicsThings/GameText.h"


struct TextRenderingSpecs {
	int fontSize, fontSizePixels;
	int margin, lineSpacing, messageSpacing;
	int maxLettersPerLine;
	int startOffset;

	TextRenderingSpecs(int fontSize = 2, int margin = 16) : fontSize(fontSize),
		fontSizePixels(8 * fontSize), margin(margin), lineSpacing(fontSizePixels / 4),
		messageSpacing(fontSizePixels / 2), startOffset(0), maxLettersPerLine(0) {};

	void modifyFontSize(int modification);
	void calcMaxLettersPerLine(int viewportWidth);
};


class TextRenderer {
private:
	SDL_Renderer* renderer;
	SDL_Texture* spritesheet;

	void renderFormattedText(TextRenderingSpecs& specs, std::string& fText, GameText& gameText, int startY);

public:
	TextRenderer() : renderer(NULL), spritesheet(NULL) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spriteSheet);

	//Renders a GameText object down from startY. Returns the ending y coordinate.
	int renderGameTextDown(TextRenderingSpecs& specs, GameText& gameText, int startY);
	//Renders a GameText object up from startY. Returns the ending y coordinate.
	int renderGameTextUp(TextRenderingSpecs& specs, GameText& gameText, int startY);

	//Renders a formatted GameText (a string and a height) down from startY. Returns ending y coordinate.
	int renderFormattedTextDown(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY);
	//Renders a formatted GameText (a string and a height) up from startY. Returns ending y coordinate.
	int renderFormattedTextUp(TextRenderingSpecs& specs, std::pair<std::string, int>& fText, GameText& gameText, int startY);

	std::pair<std::string, int> formatGameText(TextRenderingSpecs& specs, GameText& gameText);
};

#pragma once

#include "GraphicsThings/TextRenderer.h"


struct ScrollerItem {
   bool isText; //if not text, it's spacing
   int height;
   FormattedText ftext;

   ScrollerItem(int height) : isText(false), height(height) {};
   ScrollerItem(FormattedText text, GameText gtext) :  isText(true), ftext(text) {};
};

struct ItemSpecsNode {
   int startIndex;
   TextRenderingSpecs specs;
};

class Scroller {
private:
   TextRenderer renderer;
   std::vector<ScrollerItem> items;
   std::vector<ItemSpecsNode> specsNodes;
   SDL_Rect currViewport;
   int itemsHeight, scrollOffset;
   int margin, scrollMulitplier;

   TextRenderingSpecs& getSpecsForIndex(int index);

public:
   Scroller() : margin(0), scrollMulitplier(0), scrollOffset(0), itemsHeight(0) {};

	void initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet);
   void setMarginAndScrollMulitplier(int margin, int multiplier);

   void setSpecsForSubsequentItems(TextRenderingSpecs specs);
   void addItem(int height);
   void addItem(GameText& gameText);
   void render(const SDL_Rect viewport);

   void processScroll(int offset);
   void clear();
};

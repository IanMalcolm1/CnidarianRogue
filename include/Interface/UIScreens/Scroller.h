#pragma once

#include "GraphicsThings/TextRenderer.h"

enum ScrollerItemType : uint8_t {
   SCROLLITEM_SPACING,
   SCROLLITEM_TEXT,
   SCROLLITEM_LINE,
};

struct ScrollerItem {
   ScrollerItemType type; //if not text, it's spacing
   int height;
   FormattedText ftext;

   ScrollerItem(int height) : type(SCROLLITEM_SPACING), height(height) {};
   ScrollerItem(FormattedText text) :  type(SCROLLITEM_TEXT), ftext(text) {};
   ScrollerItem(ScrollerItemType type) : type(type) {};
};

struct ItemSpecsNode {
   int startIndex;
   TextRenderingSpecs specs;
};

class Scroller {
private:
   TextRenderer renderer;
   GameTextMaker textMaker;
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
   void addLineSeparator();

   void render(const SDL_Rect viewport);

   void processScroll(int x, int y, int offset);
   void clear();
};

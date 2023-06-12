#pragma once

#include "GraphicsThings/TextRenderer.h"


struct ScrollerItem {
   bool isText; //if not text, it's spacing
   int height;
   FormattedText ftext;
   GameText gtext;

   ScrollerItem(int height) : isText(false), height(height) {};
   ScrollerItem(FormattedText text, GameText gtext) :  gtext(gtext), isText(true), ftext(text) {};
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
   Scroller(int margin, int scrollMulitplier) : margin(margin),
   scrollMulitplier(scrollMulitplier), scrollOffset(0), itemsHeight(0) {};

   void setSpecsForSubsequentItems(TextRenderingSpecs specs);
   void addItem(int height);
   void addItem(GameText& gameText);
   void render(SDL_Rect& viewport);

   void processScroll(int offset);
   void clear();
};

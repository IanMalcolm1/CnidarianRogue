#include "Interface/UIScreens/Scroller.h"
#include "SDL_hidapi.h"


void Scroller::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
   this->renderer.initialize(renderer, spritesheet);
}

void Scroller::setMarginAndScrollMulitplier(int margin, int multiplier) {
   this->margin = margin;
   scrollMulitplier = multiplier;

   scrollOffset = margin;
}

void Scroller::clear() {
   items.clear();
   specsNodes.clear();
   itemsHeight = 0;
}


void Scroller::setSpecsForSubsequentItems(TextRenderingSpecs specs) {
   specsNodes.push_back({(int) items.size(), specs});
}

void Scroller::addItem(int height) {
   items.push_back(ScrollerItem(height));
   itemsHeight += height;
}

void Scroller::addItem(GameText& gameText) {
   FormattedText ftext = renderer.formatGameText(getSpecsForIndex(items.size()), gameText);
   items.push_back(ScrollerItem(ftext));
   itemsHeight += items.back().ftext.getHeight();
}

void Scroller::addLineSeparator() {
   itemsHeight += specsNodes.back().specs.fontSizePixels + 2*specsNodes.back().specs.lineSpacing;
   items.push_back(ScrollerItem(SCROLLITEM_LINE));
}


void Scroller::render(const SDL_Rect viewport) {
   currViewport = viewport;

	int startY = scrollOffset;

   for (int i=0; i<items.size(); i++) {
      ScrollerItem item = items[i];
      switch (item.type) {
      case SCROLLITEM_TEXT:
         startY = renderer.renderFormattedText(getSpecsForIndex(i), item.ftext, startY);
         break;
      case SCROLLITEM_SPACING:
         startY += item.height;
         break;
      case SCROLLITEM_LINE:
         startY = renderer.renderLineSeparator(getSpecsForIndex(i), textMaker, startY);
         break;
      }
   }
}

void Scroller::processScroll(int x, int y, int offset) {
	SDL_Point point = { x,y };
	if (!SDL_PointInRect(&point, &currViewport)) {
      return;
   }

	scrollOffset += offset * scrollMulitplier;

	if (scrollOffset > margin || itemsHeight < currViewport.h - margin) {
		scrollOffset = margin;
	}
	else if (itemsHeight + scrollOffset < currViewport.h - margin) {
		scrollOffset = currViewport.h -itemsHeight - margin;
	}
}


TextRenderingSpecs& Scroller::getSpecsForIndex(int index) {
   for (int i=0; i<specsNodes.size(); i++) {
      if (index < specsNodes[i].startIndex) {
         return specsNodes[i-1].specs;
      }
   }
   return specsNodes.back().specs;
}

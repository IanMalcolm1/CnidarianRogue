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

void Scroller::addItem(int height) {
   items.push_back(ScrollerItem(height));
   itemsHeight += height;
}


void Scroller::setSpecsForSubsequentItems(TextRenderingSpecs specs) {
   specsNodes.push_back({(int) items.size(), specs});
}

void Scroller::addItem(GameText& gameText) {
   FormattedText ftext = renderer.formatGameText(getSpecsForIndex(items.size()), gameText);
   items.push_back(ScrollerItem(ftext, gameText));
   itemsHeight += items.back().ftext.getHeight();
}

void Scroller::render(const SDL_Rect viewport) {
   currViewport = viewport;

	int startY = scrollOffset;

   for (int i=0; i<items.size(); i++) {
      ScrollerItem item = items[i];
      if (item.isText) {
         startY = renderer.renderFormattedText(getSpecsForIndex(i), item.ftext, startY);
      }
      else {
         startY += item.height;
      }
   }
}

void Scroller::processScroll(int offset) {
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

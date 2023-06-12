#include "Interface/UIScreens/Scroller.h"
#include "SDL_hidapi.h"


void Scroller::clear() {
   items.clear();
   itemsHeight = 0;
}

void Scroller::addItem(int height) {
   items.push_back(ScrollerItem(itemsHeight));
   itemsHeight += height;
}


void Scroller::setSpecsForSubsequentItems(TextRenderingSpecs specs) {
   specsNodes.push_back({(int) items.size(), specs});
}

void Scroller::addItem(GameText& gameText) {
   FormattedText ftext = renderer.formatGameText(getSpecsForIndex(items.size()), gameText);
   items.push_back(ScrollerItem(ftext, gameText));
   itemsHeight += items.back().ftext.height;
}

void Scroller::render(SDL_Rect& viewport) {
   currViewport = viewport;

	int startY = viewport.h + scrollOffset;

   for (int i=0; i<items.size(); i++) {
      ScrollerItem item = items[i];
      if (item.isText) {
         startY = renderer.renderFormattedText(getSpecsForIndex(i), item.ftext, item.gtext, startY);
      }
      else {
         startY += item.height;
      }
   }
}

void Scroller::processScroll(int offset) {
	scrollOffset += offset * scrollMulitplier;

	if (scrollOffset < -margin || itemsHeight < currViewport.h - margin) {
		scrollOffset = -margin;
	}
	else if (itemsHeight < scrollOffset + currViewport.h - margin) {
		scrollOffset = itemsHeight - currViewport.h + margin;
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

#pragma once

#include "GraphicsThings/TextRenderer.h"


struct ScrollerItem {
   bool isText; //if not text, it's spacing
   union {
      int height;
   };
};

class Scroller {
private:
   TextRenderer renderer;

public:
   void clear();

   void render();

   void processScroll(int offset);
};

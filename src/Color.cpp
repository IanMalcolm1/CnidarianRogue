#include "GraphicsThings/Color.h"

void Color::set(uint8_t red, uint8_t green, uint8_t blue) {
	r = red;
	g = green;
	b = blue;
}


std::string Color::getString() {
   std::string color = "";

   std::string value = std::to_string(r);
   if (value.size() < 3) { value.insert(0, "0"); }
   if (value.size() < 3) { value.insert(0, "0"); }
   color.append(value);

   value = std::to_string(g);
   if (value.size() < 3) { value.insert(0, "0"); }
   if (value.size() < 3) { value.insert(0, "0"); }
   color.append(value);

   value = std::to_string(b);
   if (value.size() < 3) { value.insert(0, "0"); }
   if (value.size() < 3) { value.insert(0, "0"); }
   color.append(value);

   return color;
}

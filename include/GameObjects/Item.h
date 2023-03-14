#pragma once

#include "GraphicsThings/TileDisplay.h"

class Item {
private:
	TileDisplay display;

public:
	TileDisplay* getDisplay();
};

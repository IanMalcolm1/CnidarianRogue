#pragma once

#include <SDL.h>
#include "GraphicsThings/MyColor.h"

class SDLHelper {
public:
	//Uses SDL_RenderCopy() rather than normal SDL_RenderFillRect which is incredibly slow
	static void fill(SDL_Renderer* renderer, SDL_Texture* spritesheet, const SDL_Rect& destination, MyColor color) {
		SDL_Rect sourcePixel = { 88, 104, 1, 1 }; //this is just a random pixel from the spritesheet

		SDL_SetTextureColorMod(spritesheet, color.r, color.g, color.b);
		SDL_RenderCopy(renderer, spritesheet, &sourcePixel, &destination);

		SDL_SetTextureColorMod(spritesheet, 255, 255, 255);
	}
};

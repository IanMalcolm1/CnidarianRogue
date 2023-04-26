#include "Interface/UIScreens/MapUI.h"
#include "GraphicsThings/RectFiller.h"

void MapUI::initialize(LocalMap* map, SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->map = map;
	this->mapDisplay = map->getMapDisplay();
	this->renderer = renderer;
	this->spritesheet = spritesheet;

	int textureWidth = map->getWidth() * 8;
	int textureHeight = map->getHeight() * 8;
	mapTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
		textureWidth, textureHeight);
}

MapUI::~MapUI() {
	SDL_DestroyTexture(mapTexture);
	mapTexture = NULL;
}


void MapUI::render(const SDL_Rect& viewport) {
	if (hidden) {
		return;
	}

	SDL_SetRenderTarget(renderer, mapTexture);

	mainViewport.h = viewport.h;
	mainViewport.w = viewport.w;
	mainViewport.x = viewport.x;
	mainViewport.y = viewport.y;

	calculateMapRenderingData();

	//for SDL_RenderCopy()
	SDL_Rect dstrect = { 0,0, 8, 8 };

	int index;

   for (int y = rData.startTile.y; y < rData.endTile.y+1 && y < map->getHeight(); y++) {
      for (int x = rData.startTile.x; x < rData.endTile.x; x++) {
			index = y * mapDisplay->getWidth() + x;

			if (mapDisplay->isDirty(index)) {
				dstrect.x = x * 8;
				dstrect.y = y * 8;
				renderTile(index, dstrect);
			}
		}
	}

	SDL_SetRenderTarget(renderer, NULL);

	SDL_RenderSetViewport(renderer, &viewport);

	SDL_RenderCopy(renderer, mapTexture, &rData.srcRect, &rData.dstRect);
}


void MapUI::calculateMapRenderingData() {
	calcDataForAxis(mainViewport, 'x');
	calcDataForAxis(mainViewport, 'y');

	rData.srcRect.x = rData.startTile.x * 8;
	rData.srcRect.y = rData.startTile.y * 8;
	rData.srcRect.w = (1 + rData.endTile.x - rData.startTile.x) * 8;
	rData.srcRect.h = (1 + rData.endTile.y - rData.startTile.y) * 8;
}


void MapUI::calcDataForAxis(const SDL_Rect& viewport, char axis) {
	/*
	Intent:
	The below algorithm ensures we see as many tiles as possible given the scale of the
	map and the tile being focused on. Essentially this means we don't always center the
	'camera' on the focused tile if that tile is too close to one edge and doing so would
	create empty space. Of course, if the map display would be smaller than the window's
	dimensions (aka, when we're really zoomed out), we can't really avoid empty space and
	just center the map in its viewport.
	Also trying for perfect pixel scaling, which is part of why there are so many heuristics.
	*/

	const int scaleSize = rData.scaleSize;

	int mapLengthTiles;
	int mapLengthPixels;
	int viewportLength;
	int focusTileCoord;

	int* destinationStart;
	int* destinationLength;
	int* startTileCoord;
	int* endTileCoord;

	if (axis == 'x') {
		mapLengthTiles = map->getWidth();
		mapLengthPixels = mapLengthTiles * scaleSize;
		viewportLength = viewport.w;
		focusTileCoord = mapDisplay->getFocusTile().x;

		destinationStart = &rData.dstRect.x;
		destinationLength = &rData.dstRect.w;

		startTileCoord = &rData.startTile.x;
		endTileCoord = &rData.endTile.x;
	}
	else {
		mapLengthTiles = map->getHeight();
		mapLengthPixels = mapLengthTiles * scaleSize;
		viewportLength = viewport.h;
		focusTileCoord = mapDisplay->getFocusTile().y;

		destinationStart = &rData.dstRect.y;
		destinationLength = &rData.dstRect.h;

		startTileCoord = &rData.startTile.y;
		endTileCoord = &rData.endTile.y;
	}


	if (mapLengthPixels < viewportLength) {
		//Center map in camera
		(*destinationStart) = (viewportLength - mapLengthPixels) / 2;
		(*endTileCoord) = mapLengthTiles;
		(*startTileCoord) = 0;

		(*destinationLength) = mapLengthTiles * scaleSize;
	}

	else if ((scaleSize * (mapLengthTiles - focusTileCoord) - scaleSize/2) < (viewportLength/2)) {
		//Snap camera to bottom or right edge
		(*endTileCoord) = mapLengthTiles;

		if (viewportLength % scaleSize == 0) { (*destinationStart) = 0; }
		else { (*destinationStart) = (viewportLength % scaleSize) - scaleSize; }

		(*destinationLength) = viewportLength - (*destinationStart);
		(*startTileCoord) = mapLengthTiles - (*destinationLength) / scaleSize;
	}

	else if ((scaleSize * focusTileCoord + scaleSize/2) < (viewportLength/2)) {
		//Snap camera to top or left edge
		(*destinationStart) = 0;
		(*startTileCoord) = 0;

		if (viewportLength && scaleSize == 0) {
			(*endTileCoord) = viewportLength / scaleSize;
		}
		else {
			(*endTileCoord) = viewportLength / scaleSize + 1;
		}

		(*destinationLength) = (*endTileCoord) * scaleSize + scaleSize;
	}

	else {
		//Center camera on focus tile
		int portionBehindFocusTile = viewportLength / 2 - scaleSize / 2;
		int tilesBeyondFocusTile;
		if (portionBehindFocusTile % scaleSize == 0) {
			tilesBeyondFocusTile = portionBehindFocusTile / scaleSize;
			(*startTileCoord) = focusTileCoord - tilesBeyondFocusTile;
		}
		else {
			int roundOff = (scaleSize - portionBehindFocusTile % scaleSize);
			tilesBeyondFocusTile = (portionBehindFocusTile + roundOff) / scaleSize;
			(*startTileCoord) = focusTileCoord - tilesBeyondFocusTile;
		}

		(*endTileCoord) = focusTileCoord + tilesBeyondFocusTile;

		(*destinationStart) = (viewportLength/2) - (scaleSize/2 + tilesBeyondFocusTile*scaleSize);
		(*destinationLength) = (1 + (*endTileCoord) - (*startTileCoord)) * scaleSize;
	}
}


void MapUI::renderTile(int index, SDL_Rect dstrect) {
	TileDisplay* tile = mapDisplay->getDisplay(index);
	SDL_Rect srcrect = { 0,0,8,8 };

	//unseen tiles are rendered black
	if (!mapDisplay->hasBeenSeen(index)) {
		RectFiller::fill(renderer, spritesheet, dstrect, { 0,0,0 });
		return;
	}

	//remembered but not visible tiles are faded
	if (!mapDisplay->isVisible(index)) {
		RectFiller::fill(renderer, spritesheet, dstrect, { 0,0,0 });
		SDL_SetTextureAlphaMod(spritesheet, 64);
	}
	else {
		SDL_SetTextureAlphaMod(spritesheet, 255);
	}

	//tile background
	RectFiller::fill(renderer, spritesheet, dstrect, tile->backColor);

	//tile foreground
	SDL_SetTextureColorMod(spritesheet, tile->symbolColor.r, tile->symbolColor.g, tile->symbolColor.b);

	srcrect.x = tile->symbol % 16 * 8;
	srcrect.y = tile->symbol / 16 * 8;
	SDL_RenderCopy(renderer, spritesheet, &srcrect, &dstrect);

	//reticles
	if (mapDisplay->hasReticle(index)) {
		srcrect.x = ASYM_RETICLE % 16 * 8;
		srcrect.y = ASYM_RETICLE / 16 * 8;

		SDL_SetTextureColorMod(spritesheet, 255, 255, 255);

		SDL_RenderCopy(renderer, spritesheet, &srcrect, &dstrect);
	}

	SDL_SetTextureAlphaMod(spritesheet, 255); //resets opacity
}


void MapUI::processScroll(int x, int y, int offset, bool ctrlDown) {
	if (hidden) {
		return;
	}

	SDL_Point point = { x,y };

	if (!SDL_PointInRect(&point, &mainViewport)) {
		return;
	}

	rData.scale += offset;
	if (rData.scale < 1) { rData.scale = 1; }
	else if (rData.scale > 20) { rData.scale = 20; }

	rData.scaleSize = rData.scale * 8;
}

void MapUI::processCursorLocation(int x, int y) {
	if (hidden) {
		return;
	}

	SDL_Point point = { x,y };

	if (!SDL_PointInRect(&point, &mainViewport)) {
		map->setMouseTile({ -1,-1 });
		return;
	}

	x -= mainViewport.x;
	y -= mainViewport.y;

	map->setMouseTile(findMapTileFromScreenCoords(x, y));
}


TileCoords MapUI::findMapTileFromScreenCoords(int x, int y) {
	TileCoords returnCoords = { -1,-1 };

	SDL_Point point = { x,y };
	if (!SDL_PointInRect(&point, &rData.dstRect)) {
		return returnCoords;
	}

	x -= rData.dstRect.x;
	y -= rData.dstRect.y;

	if (x % rData.scaleSize == 0) {
		returnCoords.x = x / rData.scaleSize;
		returnCoords.x += rData.startTile.x-1;
	}
	else {
		returnCoords.x = x / rData.scaleSize;
		returnCoords.x += rData.startTile.x;
	}
	returnCoords.y = rData.startTile.y + y / rData.scaleSize;

	return returnCoords;
}

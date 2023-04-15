#include "UIScreens/MessagesUI.h"


void MessagesUI::initialize(SDL_Renderer* renderer, SDL_Texture* spritesheet) {
	this->renderer = renderer;
	this->spritesheet = spritesheet;

	textRenderer.initialize(renderer, spritesheet);
}


void MessagesUI::render(const SDL_Rect& viewport) {
	SDL_RenderSetViewport(renderer, &viewport);

	std::vector<GameText>* recentMessages = log->getRecentMessages();

	if (recentMessages->size() == 0) {
		return;
	}

	mainViewport.x = viewport.x;
	mainViewport.y = viewport.y;
	mainViewport.h = viewport.h;

	if (viewport.w != mainViewport.w) {
		mainViewport.w = viewport.w;
		makeFormattedMessages();
	}
	else if (recentMessages->size() != formattedMsgs.size()) {
		makeFormattedMessages();
	}
	
	int startY = viewport.h - textSpecs.margin + textSpecs.scrollOffset;

	for (int i = formattedMsgs.size()-1; i >= 0; i--) {
		if (startY < 0) {
			break;
		}

		if (startY - formattedMsgs.at(i).second > mainViewport.h) {
			startY -= (formattedMsgs.at(i).second + textSpecs.messageSpacing);
			continue;
		}

		startY = textRenderer.renderFormattedTextUp(textSpecs, formattedMsgs.at(i), recentMessages->at(i), startY);
		startY -= textSpecs.messageSpacing;
	}
}

void MessagesUI::processScroll(int x, int y, int offset, bool ctrlDown) {
	SDL_Point point = { x,y };

	if (!SDL_PointInRect(&point, &mainViewport)) {
		return;
	}

	if (ctrlDown) {
		textSpecs.modifyFontSize(offset);
		makeFormattedMessages();
	}
	else {
		textSpecs.scrollOffset += offset * textSpecs.fontSizePixels;
	}

	if (textSpecs.scrollOffset < 0 || totalHeight < mainViewport.h - 2 * textSpecs.margin) {
		textSpecs.scrollOffset = 0;
	}
	else if (totalHeight < textSpecs.scrollOffset + mainViewport.h - textSpecs.margin) {
		textSpecs.scrollOffset = totalHeight - (mainViewport.h - 2*textSpecs.margin);
	}
}

void MessagesUI::makeFormattedMessages() {
	std::vector<GameText>* recentMessages = log->getRecentMessages();
	int entriesAdded;

	textSpecs.calcMaxLettersPerLine(mainViewport.w);

	entriesAdded = recentMessages->size() - formattedMsgs.size();

	if (entriesAdded<=0) {
		formattedMsgs.clear();
		totalHeight = 0;
		entriesAdded = recentMessages->size();
	}

	std::pair<std::string, int> fMessage;
	for (int i = formattedMsgs.size(); i < recentMessages->size(); i++) {
		fMessage = textRenderer.formatGameText(textSpecs, recentMessages->at(i));
		totalHeight += fMessage.second;
		formattedMsgs.push_back(fMessage);
	}

	totalHeight += (entriesAdded - 1) * textSpecs.messageSpacing;
}

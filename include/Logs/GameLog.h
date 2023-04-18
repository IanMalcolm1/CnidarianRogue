#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "GraphicsThings/MyColor.h"
#include "DebugLogger.h"
#include "GraphicsThings/ColorMap.h"
#include "GraphicsThings/GameText.h"

class GameLog {
private:
	std::fstream messageFile;
	std::vector<GameText> recentMessages;
	GameTextMaker gameTextMaker;

public:
	GameLog();
	~GameLog();

   //See GameText.h for formatting guidelines
	void sendMessage(std::string text);

	std::vector<GameText>* getRecentMessages();
};

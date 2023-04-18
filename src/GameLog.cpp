#include "Logs/GameLog.h"
#include <stack>
#include <filesystem>
#include <iostream>


GameLog::GameLog() {
   if (!std::filesystem::is_directory("logs")) {
      std::filesystem::create_directory("logs");
   }

	messageFile = std::fstream();
	messageFile.open("logs/message_log.txt", std::ios::in | std::ios::out | std::ios::trunc);

	if ( !messageFile.is_open() ) {
		printf("Failed to open message log file.");
	}

	gameTextMaker = GameTextMaker();
}

GameLog::~GameLog() {
	messageFile.close();
}

void GameLog::sendMessage(std::string text) {
	messageFile.write(text.c_str(), text.size());
	messageFile.write("\n", 1);

	recentMessages.push_back( gameTextMaker.makeGameText(text) );
}

std::vector<GameText>* GameLog::getRecentMessages() { return &recentMessages; }

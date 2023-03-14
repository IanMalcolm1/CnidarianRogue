#include "Logs/GameLog.h"
#include <stack>


GameLog::GameLog() {
	debugLogger = std::make_unique<DebugLogger>();

	messageFile = std::make_unique<std::fstream>();
	messageFile->open("game_files/message_log.txt", std::ios::in | std::ios::out | std::ios::app);

	if ( !messageFile->is_open() ) {
		printf("Failed to open message log file.");
	}

	gameTextMaker = std::make_unique<GameTextMaker>();
}

GameLog::~GameLog() {
	messageFile->close();
}

void GameLog::sendMessage(std::string text) {
	messageFile->write(text.c_str(), text.size());
	messageFile->write("\n", 1);

	recentMessages.push_back( gameTextMaker->makeGameText(text) );
}

std::vector<GameText>* GameLog::getRecentMessages() { return &recentMessages; }

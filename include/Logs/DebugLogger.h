#pragma once

#include <fstream>
#include <memory>

#define DEBUG_LOG_FILEPATH "game_files/debug_log.txt"

//Not thread-safe. Might want to make a buffer of debug messages, and only
// write to file at every 5 messages or at destruction (if I decide to add
// threads at some point)
class DebugLogger {
private:
	std::unique_ptr<std::fstream> debugFile;

public:
	DebugLogger();
	~DebugLogger();

	void log(std::string text);
};

#pragma once

#include <chrono>
#include <fstream>
#include <memory>

#define DEBUG_LOG_FILEPATH "game_files/debug_log.txt"

//Not thread-safe. Might want to make a buffer of debug messages, and only
// write to file at every 5 messages or at destruction (if I decide to add
// threads at some point)
class DebugLogger {
private:
   static inline bool setupDone = false;
   static inline std::chrono::time_point<std::chrono::steady_clock> startTime;
   static inline std::fstream debugFile;

   static void setupDebugFile();

public:
	static void log(std::string text);
   static void closeDebugLogger();
};

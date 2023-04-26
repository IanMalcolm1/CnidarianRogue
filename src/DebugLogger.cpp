#include "Logs/DebugLogger.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

void DebugLogger::log(std::string text) {
   if (!DebugLogger::setupDone) {
      DebugLogger::setupDebugFile();
   }


   auto now = std::chrono::steady_clock::now();
   std::string timeText = std::string();
   std::chrono::duration<double> diff = now-startTime;

   timeText.append("\nTime: ");
   timeText.append( std::to_string(diff.count()) );
   timeText.append("s after initialization.");
   
	DebugLogger::debugFile.write(text.c_str(), text.size());
   DebugLogger::debugFile.write(timeText.c_str(), timeText.size());
	DebugLogger::debugFile.write("\n\n",2);

	printf("%s\n\n", text.c_str());
}


void DebugLogger::setupDebugFile() {
   DebugLogger::startTime = std::chrono::steady_clock::now();
   DebugLogger::setupDone = true;

   if (!std::filesystem::is_directory("logs")) {
      std::filesystem::create_directory("logs");
   }


   DebugLogger::debugFile = std::fstream();
   DebugLogger::debugFile.open("logs/debug_log.txt", std::ios::in | std::ios::out | std::ios::trunc);
	if (!DebugLogger::debugFile.is_open()) {
		printf("Failed to open debug log file.");
	}
}


void DebugLogger::closeDebugLogger() {
   debugFile.close();
}

#include "Logs/DebugLogger.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

void DebugLogger::log(std::string text) {
   if (!DebugLogger::startTimeRecorded) {
      DebugLogger::startTime = std::chrono::steady_clock::now();
      DebugLogger::startTimeRecorded = true;
   }
   if (!std::filesystem::is_directory("logs")) {
      std::filesystem::create_directory("logs");
   }


   std::fstream debugFile = std::fstream();
	debugFile.open("logs/debug_log.txt", std::ios::in | std::ios::out | std::ios::trunc);
	if (!debugFile.is_open()) {
		printf("Failed to open debug log file.");
	}


   auto now = std::chrono::steady_clock::now();
   std::string timeText = std::string();
   std::chrono::duration<double> diff = now-startTime;

   timeText.append("\nAt: ");
   timeText.append( std::to_string(diff.count()) );
   timeText.append("s after initialization.");
   
	debugFile.write(text.c_str(), text.size());
   debugFile.write(timeText.c_str(), timeText.size());
	debugFile.write("\n\n",2);

	printf("%s\n\n", text.c_str());

	debugFile.close();
}

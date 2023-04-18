#include "Logs/DebugLogger.h"
#include <filesystem>

DebugLogger::DebugLogger() {
   if (!std::filesystem::is_directory("logs")) {
      std::filesystem::create_directory("logs");
   }

	debugFile = std::fstream("logs/debug_log.txt");
	debugFile.open("logs/debug_log.txt", std::ios::in | std::ios::out | std::ios::trunc);

	if (!debugFile.is_open()) {
		printf("Failed to open debug log file.");
	}
}

DebugLogger::~DebugLogger() {
	debugFile.close();
}

void DebugLogger::log(std::string text) {
	printf("%s\n\n", text.c_str());

	debugFile.write(text.c_str(), text.size());
	debugFile.write("\n\n",2);
}

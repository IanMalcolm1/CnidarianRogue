#include "Logs/DebugLogger.h"

DebugLogger::DebugLogger() {
	debugFile = std::make_unique<std::fstream>();

	debugFile->open(DEBUG_LOG_FILEPATH, std::ios::out | std::ios::app);

	if (!debugFile->is_open()) {
		printf("Failed to open debug log file.");
		return;
	}
}

DebugLogger::~DebugLogger() {
	debugFile->close();
}

void DebugLogger::log(std::string text) {
	printf("%s\n\n", text.c_str());

	debugFile->write(text.c_str(), text.size());
	debugFile->write("\n\n",2);
}

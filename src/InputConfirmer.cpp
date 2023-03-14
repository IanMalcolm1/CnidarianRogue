#include "UIScreens/InputConfirmer.h"

void InputConfirmer::signalPopup(PlayerCommand command, std::string message) {
	awaiting = true;
	this->command = command;
	this->message = message;
}

int InputConfirmer::getConfirmation() {
	if (confirmation != -1) {
		int temp = confirmation;
		confirmation = -1;
		awaiting = false;
		return temp;
	}
	return -1;
}

void InputConfirmer::setConfirmation(int con) {
	confirmation = con;
	if (confirmation == 0) {
		command = PC_NULL;
	}
}

bool InputConfirmer::isAwaiting() {
	return awaiting;
}

PlayerCommand InputConfirmer::getCommand() {
	return command;
}

bool InputConfirmer::commandEquals(PlayerCommand command) {
	if (this->command == command) {
		this->command = PC_NULL;
		return true;
	}
	return false;
}

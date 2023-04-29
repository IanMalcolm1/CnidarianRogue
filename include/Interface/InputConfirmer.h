#pragma once

#include "Enums/PlayerCommands.h"
#include <string>

enum ConfirmCodes {
	CONF_WAITING = -1,
	CONF_CANCELLED,
	CONF_CONFIRMED
};

//Essentially just a flagger for a ConfirmUI
struct InputConfirmer {
private:
	int confirmation; //-1 is null or not received, 0 is false, 1 is true
	bool awaiting;
	PlayerCommand command;

public:
	std::string message;

	InputConfirmer() : awaiting(false), confirmation(-1), command(PC_NULL) {};

	void signalPopup(PlayerCommand command, std::string message);

	int getConfirmation();
	void setConfirmation(int con);

	bool isAwaiting();

	PlayerCommand getCommand();
	bool commandEquals(PlayerCommand command);
};

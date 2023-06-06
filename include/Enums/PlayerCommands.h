#ifndef PLAYERCOMMANDS_H
#define PLAYERCOMMANDS_H


/*
Commands a player might use.
Generally processed along with an SDL_keymod

Movement commands are from 0 to 9 inclusive
*/
enum PlayerCommand {
	//Gameplay commands
	PC_NORTH = 0,
	PC_NORTH_EAST,
	PC_NORTH_WEST,
	PC_SOUTH,
	PC_SOUTH_EAST,
	PC_SOUTH_WEST = 5,
	PC_EAST = 7, //keeps the directions in multiples of 3 so I can use %3 to determine if has an E/W component
	PC_WEST,
	PC_WAIT = 9, //To wait 1 turn
	PC_REST, //To wait until healed
	PC_PICKUP, //To begin pickup dialogue
	PC_SHOOT, //To begin shoot dialogue
	PC_THROW, //To begin throw dialogue
	PC_TOGGLE_LOOK, //To begin/end looking around
   PC_TOGGLE_SELECT,
   PC_CHANGE_LEVEL,
   PC_CONFIRM,

	PC_END_OF_PLAYER_ACTIONS,

	//General Commands

	//UI Commands
	PC_START_OF_UI_COMMANDS,

	PC_INVENTORY, //To hightlight/unhighlight the inventory screen from the keyboard
	PC_LOG, //To highlight/unhighlight the message log from the keyboard (for scrolling)
	PC_CHARACTER_SHEET, //To open character sheet
	PC_ACTION_MENU, //To open actions pop-up menu

	//other
	PC_START_OF_OTHER,
	
	PC_ESCAPEKEY,

	PC_QUITGAME,
	PC_NULL
};

#endif

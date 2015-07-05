#include <ncurses.h>

#include "interface/Input.h"

Command Input::getInput()
{
	//Retrieve a keystroke from the player
	int ch = getch();

	//Translate the keystroke and return the Command
	return _keymap.getCommand(ch);
}


#include <ncurses.h>

#include "interface/Input.h"

Command Input::getInput()
{
	//Retrieve a keystroke from the player
	int ch = getch();

	//Translate the keystroke and return the Command
	return _keymap.getCommand(ch);
}

XYPair getMoveBy(Command cmd)
{
	//Start with zero movement
	XYPair move_by = { 0,0 };

	//First we catch the X movement; this lets us collapse several conditions
	//into fewer lines of code.
	switch(cmd)
	{
		case MOVE_E:
		case MOVE_NE:
		case MOVE_SE:
		case VIEW_RIGHT:
			move_by.x = 1;
			break;

		case MOVE_W:
		case MOVE_NW:
		case MOVE_SW:
		case VIEW_LEFT:
			move_by.x = -1;
			break;

		default:
			//This is effectively a no-op, but doesn't hurt either
			move_by.x = 0;
			break;
	}

	//Now catch Y movement
	switch(cmd)
	{
		case MOVE_N:
		case MOVE_NE:
		case MOVE_NW:
		case VIEW_UP:
			move_by.y = -1; //Remember, {0,0} is top left
			break;

		case MOVE_S:
		case MOVE_SE:
		case MOVE_SW:
		case VIEW_DOWN:
			move_by.y = 1;
			break;

		default:
			//Again just a no-op
			move_by.y = 0;
			break;
	}

	return move_by;
}


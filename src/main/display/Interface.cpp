#include <ncurses.h>

#include "display/Interface.h"

Interface::Interface()
{
	//Initialized the screen
	initscr();
	//Start with a clean slate
	clear();
	//Don't echo entered characters on the screen
	noecho();
	//Enable getting function keys
	keypad(stdscr, true);

	//Hide the cursor
	curs_set(false);

	//And finally start everything up
	refresh();
}

Interface::~Interface()
{
	endwin();
}

XYPair Interface::getScreenSize()
{
	XYPair screen;
	getmaxyx(stdscr, screen.y, screen.x);

	return screen;
}

void Interface::pause()
{
	//Save current tty modes
	def_prog_mode();
	//End ncurses mode
	endwin();
}

void Interface::resume()
{
	//Return to previous mode
	reset_prog_mode();
	//Refresh the screen to restore contents
	refresh();
}


#include <stdint.h>
#include <ncurses.h>

#include "display/Screen.h"

Screen::Screen()
{
	//Initialized the screen
	initscr();
	//Start with a clean slate
	clear();
	//Don't echo entered characters on the screen
	noecho();

	//Hide the cursor
	curs_set(false);

	//Get our height and width for later
	getmaxyx(stdscr, _height, _width);
}

Screen::~Screen()
{
	endwin();
}

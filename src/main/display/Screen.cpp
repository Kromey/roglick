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

	//Refresh the screen (to our blank state)
	/// @todo Why does it seem necessary to refresh() before we draw anything?
	///       Only required when going straight into multiple windows?
	refresh();

	//Get our height and width for later
	getmaxyx(stdscr, _height, _width);
}

Screen::~Screen()
{
	endwin();
}

uint32_t Screen::getHeight()
{
	return _height;
}

uint32_t Screen::getWidth()
{
	return _width;
}

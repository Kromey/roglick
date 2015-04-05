#include <stdint.h>
#include <ncurses.h>

#include "display/Screen.h"

Screen::Screen()
{
	initscr();
	clear();
	noecho();

	getmaxyx(stdscr, _height, _width);
}

Screen::~Screen()
{
	endwin();
}

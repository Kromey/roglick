#include <ncurses.h>
#include <stdint.h>

#include "display/Screen.h"

int main()
{
	Screen screen;

	//printw("Starting curses mode with multiple windows...");
	//refresh();

	//getch();

	uint32_t screen_y = screen.getHeight();
	uint32_t screen_x = screen.getWidth();

	screen_y = 40;
	screen_x = 40;

	WINDOW* top = newwin(1, screen_x, 0, 0);
	WINDOW* left = newwin(screen_y-1, 10, 1, 0);
	WINDOW* right = newwin(screen_y-1, screen_x-10, 1, 10);

	mvwprintw(top, 0, 0, "Top");
	mvwprintw(left, 0, 0, "Left");
	mvwprintw(right, 0, 0, "Right");

	wrefresh(top);
	wrefresh(left);
	wrefresh(right);

	getch();
}

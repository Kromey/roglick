#include <ncurses.h>
#include <stdint.h>

#include "display/Screen.h"

int main()
{
	Screen screen;

	uint32_t screen_y = screen.getHeight();
	uint32_t screen_x = screen.getWidth();

	WINDOW* top = newwin(3, screen_x, 0, 0);
	WINDOW* left = newwin(screen_y-2, 20, 2, 0);
	WINDOW* right = newwin(screen_y-2, screen_x-19, 2, 19);

	wborder(top, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(left, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(right, '|', '|', '-', '-', '+', '+', '+', '+');

	mvwprintw(top, 0, 1, "Message Panel");
	mvwprintw(left, 0, 1, "Stat Panel");
	mvwprintw(right, 0, 1, "Main Panel");

	wrefresh(top);
	wrefresh(left);
	wrefresh(right);

	getch();
}

#include <ncurses.h>
#include <stdint.h>

#include "display/Screen.h"
#include "map/Level.h"
#include "map/filters/DrunkardsWalkFilter.h"

int main()
{
	Screen screen;

	uint32_t screen_y = screen.getHeight();
	uint32_t screen_x = screen.getWidth();

	//Create a window for our map; window (and map) are double screen size)
	uint32_t map_y = screen_y * 2;
	uint32_t map_x = screen_x * 2;
	WINDOW* map = newwin(map_y, map_x, 0, 0);
	//Generate a map
	Level cave(map_y, map_x);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	//Now put the map into our map window
	for(uint32_t x = 0; x < cave.getWidth(); x++)
	{
		for(uint32_t y = 0; y < cave.getHeight(); y++)
		{
			mvwaddch(map, x+1, y, cave[x][y].getDisplay());
		}
	}

	WINDOW* top = newwin(3, screen_x, 0, 0);
	WINDOW* left = newwin(screen_y-2, 20, 2, 0);
	//WINDOW* main = newwin(screen_y-2, screen_x-19, 2, 19);
	WINDOW* main = subwin(map, screen_y-3, screen_x-20, 3, 20);

	wborder(top, '|', '|', '-', '-', '+', '+', '+', '+');
	wborder(left, '|', '|', '-', '-', '+', '+', '+', '+');
	//wborder(main, '|', '|', '-', '-', '+', '+', '+', '+');

	mvwprintw(top, 0, 1, "Message Panel");
	mvwprintw(left, 0, 1, "Stat Panel");
	//mvwprintw(main, 0, 1, "Main Panel");

	//Center the map viewport
	uint32_t map_view_y = map_y/2 - (screen_y-3)/2;
	uint32_t map_view_x = map_x/2 - (screen_x-20)/2;
	uint32_t map_view_max_y = screen_y - 3;
	uint32_t map_view_max_x = screen_x - 20;
	mvderwin(main, map_view_y, map_view_x);

	wrefresh(top);
	wrefresh(left);
	wrefresh(main);

	int ch;
	bool run = true;
	while(run)
	{
		ch = getch();

		switch(ch)
		{
			case KEY_UP:
				if(0 < map_view_y)
				{
					mvwprintw(top, 1, 1, "Up");
					map_view_y--;
				}
				break;
			case KEY_DOWN:
				if(map_view_max_y > map_view_y)
				{
					mvwprintw(top, 1, 1, "Down");
					map_view_y++;
				}
				break;
			case KEY_LEFT:
				if(0 < map_view_x)
				{
					mvwprintw(top, 1, 1, "Left");
					map_view_x--;
				}
				break;
			case KEY_RIGHT:
				if(map_view_max_x > map_view_x)
				{
					mvwprintw(top, 1, 1, "Right");
					map_view_x++;
				}
				break;
			case 'q':
			case 'Q':
				run = false;
				break;
		}

		mvderwin(main, map_view_y, map_view_x);
		wrefresh(main);
		wrefresh(top);
	}
}

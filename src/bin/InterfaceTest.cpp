#include <ncurses.h>
#include <stdint.h>
#include <iostream>
#include <unistd.h>
#include <string>

#include "display/Screen.h"
#include "display/Window.h"
#include "display/ViewportWindow.h"
#include "map/Level.h"
#include "map/filters/DrunkardsWalkFilter.h"

void pause_curses(Screen& screen)
{
	screen.pause();

	std::cout << "Paused ncurses..." << std::endl;

	sleep(4);

	std::cout << "Resuming..." << std::endl;

	sleep(1);
}

int main()
{
	Screen screen;

	uint32_t screen_y = screen.getHeight();
	uint32_t screen_x = screen.getWidth();

	//Create a window for our map; window (and map) are double screen size)
	uint32_t map_y = screen_y * 2;
	uint32_t map_x = screen_x * 2;
	ViewportWindow map(map_x, map_y, screen_x-20, screen_y-3, 20, 3);
	//Generate a map
	Level cave(map_x, map_y);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	//Now put the map into our map window
	for(uint32_t x = 0; x < cave.getWidth(); x++)
	{
		for(uint32_t y = 0; y < cave.getHeight(); y++)
		{
			map.add(x, y, cave[x][y].getDisplay());
		}
	}

	Window top(screen_x, 3, 0, 0);
	Window left(20, screen_y-2, 0, 2);

	top.addBorder();
	left.addBorder();
	//map.addBorder(); //Dare I try it?

	top.add(1, 0, "Message Panel");
	left.add(1, 0, "Stat Panel");

	//Center the map viewport
	uint32_t map_view_y = map_y/2 - (screen_y-3)/2;
	uint32_t map_view_x = map_x/2 - (screen_x-20)/2;
	uint32_t map_view_max_y = screen_y - 3;
	uint32_t map_view_max_x = screen_x - 20;
	map.move(map_view_x, map_view_y);

	//Display our windows.
	top.refresh();
	left.refresh();
	map.refresh();

	//Now we enter the "game loop"
	int ch;
	bool run = true;
	while(run)
	{
		ch = getch();

		//Display the character in our "stats" window for now
		left.add(1, 1, "     ");
		left.add(1, 1, std::to_string(ch));
		left.refresh();

		top.add(1, 1, "     ");
		switch(ch)
		{
			case KEY_UP:
				if(0 < map_view_y)
				{
					top.add(1, 1, "Up");
					map_view_y--;
				}
				break;
			case KEY_DOWN:
				if(map_view_max_y > map_view_y)
				{
					top.add(1, 1, "Down");
					map_view_y++;
				}
				break;
			case KEY_LEFT:
				if(0 < map_view_x)
				{
					top.add(1, 1, "Left");
					map_view_x--;
				}
				break;
			case KEY_RIGHT:
				if(map_view_max_x > map_view_x)
				{
					top.add(1, 1, "Right");
					map_view_x++;
				}
				break;
			case 'p':
			case 'P':
				pause_curses(screen);
				break;
			case 'q':
			case 'Q':
				run = false;
				break;
		}

		//Move the viewport
		// @todo The move method handles bounds checking, remove it from above
		map.move(map_view_x, map_view_y);

		//Refresh map view and top message window
		map.refresh();
		top.refresh();
	}
}

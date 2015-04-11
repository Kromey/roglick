#include <ncurses.h>
#include <stdint.h>
#include <iostream>
#include <unistd.h>

#include "display/Screen.h"
#include "display/Window.h"
#include "display/LevelWindow.h"
#include "display/WindowManager.h"
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

	//Make a map double the screen size
	uint32_t map_y = screen_y * 2;
	uint32_t map_x = screen_x * 2;
	//Generate a map
	Level cave(map_x, map_y);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	//Now put the map into our map window
	LevelWindow map(&cave, screen_x-20, screen_y-3, 20, 3);

	Window top(screen_x, 3, 0, 0);
	Window left(20, screen_y-2, 0, 2);

	top.addBorder();
	left.addBorder();
	//map.addBorder(); //Dare I try it?
	//Push our windows into our WindowManager
	WindowManager wm;
	wm.addWindow(&top);
	wm.addWindow(&left);
	wm.addWindow(&map);

	wm.getWindow(0)->add(1, 0, "Message Panel");
	wm.getWindow(1)->add(1, 0, "Stat Panel");

	//Center the map viewport
	uint32_t map_view_y = map_y/2 - (screen_y-3)/2;
	uint32_t map_view_x = map_x/2 - (screen_x-20)/2;
	map.move(map_view_x, map_view_y);

	//Let's display some map display stats
	//Display our view's X and Y coordinates
	wm.getWindow(1)->add(1, 2, "View Position:");
	wm.getWindow(1)->add(1, 3, "X:     ");
	wm.getWindow(1)->addInt(4, 3, map.getViewX());
	wm.getWindow(1)->add(1, 4, "Y:     ");
	wm.getWindow(1)->addInt(4, 4, map.getViewY());

	//Display map size
	wm.getWindow(1)->add(1, 6, "Map Size:");
	wm.getWindow(1)->add(1, 7, "W:");
	wm.getWindow(1)->addInt(4, 7, cave.getWidth());
	wm.getWindow(1)->add(1, 8, "H:");
	wm.getWindow(1)->addInt(4, 8, cave.getHeight());

	//Display viewport size
	wm.getWindow(1)->add(1, 9, "View Size:");
	wm.getWindow(1)->add(1, 10, "W:");
	wm.getWindow(1)->addInt(4, 10, map.getViewWidth());
	wm.getWindow(1)->add(1, 11, "H:");
	wm.getWindow(1)->addInt(4, 11, map.getViewHeight());

	//Now display everything
	wm.refresh();

	//Now we enter the "game loop"
	int ch;
	bool run = true;
	while(run)
	{
		ch = getch();

		//Display the key code
		wm.getWindow(0)->add(8, 1, "     ");
		wm.getWindow(0)->addInt(8, 1, ch);

		map_view_x = map.getViewX();
		map_view_y = map.getViewY();

		wm.getWindow(0)->add(1, 1, "     ");
		switch(ch)
		{
			case KEY_UP:
				wm.getWindow(0)->add(1, 1, "Up");
				map_view_y--;
				break;
			case KEY_DOWN:
				wm.getWindow(0)->add(1, 1, "Down");
				map_view_y++;
				break;
			case KEY_LEFT:
				wm.getWindow(0)->add(1, 1, "Left");
				map_view_x--;
				break;
			case KEY_RIGHT:
				wm.getWindow(0)->add(1, 1, "Right");
				map_view_x++;
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

		//Display our view's X and Y coordinates
		wm.getWindow(1)->add(1, 3, "X:     ");
		wm.getWindow(1)->addInt(4, 3, map.getViewX());
		wm.getWindow(1)->add(1, 4, "Y:     ");
		wm.getWindow(1)->addInt(4, 4, map.getViewY());

		//Refresh the display
		wm.refresh();
	}
}

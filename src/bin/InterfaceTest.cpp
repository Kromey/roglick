#include <ncurses.h>
#include <iostream>
#include <unistd.h>
#include <algorithm>

#include "display/Screen.h"
#include "display/Window.h"
#include "display/WindowManager.h"
#include "map/Level.h"
#include "map/filters/DrunkardsWalkFilter.h"
#include "actor/Actor.h"
#include "core/Rand.h"

void pause_curses(Screen& screen)
{
	screen.pause();

	std::cout << "Paused ncurses..." << std::endl;

	sleep(4);

	std::cout << "Resuming..." << std::endl;

	sleep(1);
}

bool move_pc(Actor& pc, Level& level, int& pc_x, int& pc_y, int dx, int dy)
{
	int new_x = pc_x + dx;
	int new_y = pc_y + dy;

	//Make sure it's in bounds
	if(0 <= new_x && new_x < level.getWidth() && 0 <= new_y && new_y < level.getHeight())
	{
		//Make sure it's passable terrain
		if(level[new_x][new_y].getPassable())
		{
			//Remove the PC from its old position
			level[pc_x][pc_y].removeActor();

			//Adjust PC's x,y coordinates
			pc_x += dx;
			pc_y += dy;

			//Place the PC at the new x,y coordinates
			level[pc_x][pc_y].addActor(&pc);

			return true;
		}
	}
	return false;
}

void spawn_npc(Actor& npc, Level& level, int& npc_x, int& npc_y, int pc_x, int pc_y, int max_dist = 35)
{
	Rand rand(time(NULL));

	int min_x = std::max(0, pc_x - max_dist);
	int max_x = std::min(level.getWidth()-1, pc_x + max_dist);

	int min_y = std::max(0, pc_y - max_dist);
	int max_y = std::min(level.getHeight()-1, pc_y + max_dist);

	do {
		npc_x = rand.randInt(min_x, max_x);
		npc_y = rand.randInt(min_y, max_y);
	} while(level[npc_x][npc_y] != FloorTile);
	level[npc_x][npc_y].addActor(&npc);
}

int main()
{
	Screen screen;

	int screen_y = screen.getHeight();
	int screen_x = screen.getWidth();

	//Make a map double the screen size
	int map_y = screen_y * 2;
	int map_x = screen_x * 2;
	//Generate a map
	Level cave(map_x, map_y);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	//Find a random FloorTile to put our PC on
	int pc_x, pc_y;
	Actor pc('@', "PC", 0x01);
	Rand rand(time(NULL));
	do {
		pc_x = rand.randInt(0, cave.getWidth()-1);
		pc_y = rand.randInt(0, cave.getHeight()-1);
	} while(cave[pc_x][pc_y] != FloorTile);
	cave[pc_x][pc_y].addActor(&pc);
	//Now put the map into our map window...
	Window level_window(&cave);
	//...and create a viewport looking into it.
	Window map(&level_window, screen_x-20, screen_y-3, 20, 3);

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

	//Center the map viewport on the PC
	map.center(pc_x, pc_y);

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

	//Display PC's location
	wm.getWindow(1)->add(1, 12, "PC Position:");
	wm.getWindow(1)->add(1, 13, "X:     ");
	wm.getWindow(1)->addInt(4, 13, pc_x);
	wm.getWindow(1)->add(1, 14, "Y:     ");
	wm.getWindow(1)->addInt(4, 14, pc_y);

	//Find a random FloorTile to put our kobold on
	int npc_x, npc_y;
	Actor npc('k', "kobold", 0x00);
	spawn_npc(npc, cave, npc_x, npc_y, pc_x, pc_y, 50);

	//Now display everything
	wm.refresh();

	//Now we enter the "game loop"
	int ch;
	int key_pos = 8;
	int last_key_pos;
	int dx, dy;
	bool run = true;
	while(run)
	{
		ch = getch();

		//Display the key code
		wm.getWindow(0)->add(key_pos, 1, "                                    ");
		wm.getWindow(0)->addInt(key_pos, 1, ch);

		dx = 0;
		dy = 0;

		wm.getWindow(0)->add(1, 1, "     ");
		last_key_pos = key_pos;
		key_pos = 8;
		switch(ch)
		{
			//Viewport movement
			case KEY_UP:
				wm.getWindow(0)->add(1, 1, "Up");
				dy = -1;
				break;
			case KEY_DOWN:
				wm.getWindow(0)->add(1, 1, "Down");
				dy = 1;
				break;
			case KEY_LEFT:
				wm.getWindow(0)->add(1, 1, "Left");
				dx = -1;
				break;
			case KEY_RIGHT:
				wm.getWindow(0)->add(1, 1, "Right");
				dx = 1;
				break;
			//Orthogonal movement
			case '8':
			case 'k':
				move_pc(pc, cave, pc_x, pc_y, 0, -1);
				break;
			case '2':
			case 'j':
				move_pc(pc, cave, pc_x, pc_y, 0, 1);
				break;
			case '4':
			case 'h':
				move_pc(pc, cave, pc_x, pc_y, -1, 0);
				break;
			case '6':
			case 'l':
				move_pc(pc, cave, pc_x, pc_y, 1, 0);
				break;
			//Diagonal movement
			case '7':
			case 'y':
				move_pc(pc, cave, pc_x, pc_y, -1, -1);
				break;
			case '9':
			case 'u':
				move_pc(pc, cave, pc_x, pc_y, 1, -1);
				break;
			case '1':
			case 'b':
				move_pc(pc, cave, pc_x, pc_y, -1, 1);
				break;
			case '3':
			case 'n':
				move_pc(pc, cave, pc_x, pc_y, 1, 1);
				break;
			//Other commands
			case 'c':
			case 'C':
				//Center the view on the PC
				wm.getWindow(2)->center(pc_x, pc_y);
				break;
			case 'p':
			case 'P':
				//Pause ncurses (just a useless demo of the ability)
				pause_curses(screen);
				break;
			case 'q':
			case 'Q':
				//Quit
				run = false;
				break;
			default:
				key_pos = last_key_pos + 4;
				if(key_pos > wm.getWindow(0)->getWidth())
				{
					key_pos = 8;
				}
				break;
		}

		//If the PC "killed" the kobold, spawn another
		if(npc_x == pc_x && npc_y == pc_y)
		{
			spawn_npc(npc, cave, npc_x, npc_y, pc_x, pc_y);
		}

		//Move the viewport
		map.moveBy(dx, dy);

		//Display our view's X and Y coordinates
		wm.getWindow(1)->add(1, 3, "X:     ");
		wm.getWindow(1)->addInt(4, 3, map.getViewX());
		wm.getWindow(1)->add(1, 4, "Y:     ");
		wm.getWindow(1)->addInt(4, 4, map.getViewY());

		//Re-display PC's position
		wm.getWindow(1)->add(1, 13, "X:     ");
		wm.getWindow(1)->addInt(4, 13, pc_x);
		wm.getWindow(1)->add(1, 14, "Y:     ");
		wm.getWindow(1)->addInt(4, 14, pc_y);

		//Display NPC's position
		wm.getWindow(1)->add(1, 15, "NPC Position:");
		wm.getWindow(1)->add(1, 16, "X:     ");
		wm.getWindow(1)->addInt(4, 16, npc_x);
		wm.getWindow(1)->add(1, 17, "Y:     ");
		wm.getWindow(1)->addInt(4, 17, npc_y);

		//Refresh the display
		wm.refresh();
	}
}

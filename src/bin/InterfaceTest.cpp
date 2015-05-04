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
#include "actor/Skill.h"
#include "core/Rand.h"

#include "entity/ecs.h"

void pause_curses(Screen& screen)
{
	screen.pause();

	std::cout << "Paused ncurses..." << std::endl;

	sleep(4);

	std::cout << "Resuming..." << std::endl;

	sleep(1);
}

bool fight_npc(Skill& pc_atk, Skill& npc_def, Window* msg_win)
{
	if(!pc_atk.check())
	{
		msg_win->add(1, 1, "You missed the kobold!");
		return false;
	}

	//DoS of the attack is a penalty on the defense
	if(npc_def.check(-1 * pc_atk.getDoS()))
	{
		msg_win->add(1, 1, "The kobold dodged your attack!");
		return false;
	}

	msg_win->add(1, 1, "You hit the kobold! You have slain the kobold!");
	return true;
}

bool move_pc(Actor& pc, Level& level, int& pc_x, int& pc_y, int dx, int dy)
{
	int new_x = pc_x + dx;
	int new_y = pc_y + dy;

	//Make sure it's in bounds
	if(0 <= new_x && new_x < level.getWidth() && 0 <= new_y && new_y < level.getHeight())
	{
		//Make sure it's passable terrain
		if(level[new_x][new_y].isPassable())
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

void spawn_npc(Level& level, PositionComponent& npc_pos, PositionComponent& pc_pos, int max_dist = 35)
{
	Rand rand(time(NULL));

	int min_x = std::max(0, pc_pos.x - max_dist);
	int max_x = std::min(level.getWidth()-1, pc_pos.x + max_dist);

	int min_y = std::max(0, pc_pos.y - max_dist);
	int max_y = std::min(level.getHeight()-1, pc_pos.y + max_dist);

	do {
		npc_pos.x = rand.randInt(min_x, max_x);
		npc_pos.y = rand.randInt(min_y, max_y);
	} while(level[npc_pos.x][npc_pos.y] != FloorTile);
}

int main()
{
	Screen screen;
	EntityManager em;

	//Set up our ComponentManagers
	PositionManager pm;
	SpriteManager sm;
	em.addComponentManager(&pm);
	em.addComponentManager(&sm);

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
	Entity pc = em.createEntity();
	PositionComponent pc_pos;
	SpriteComponent pc_sprite = { '@', 0, 0 };
	Rand rand(time(NULL));
	do {
		pc_pos.x = rand.randInt(0, cave.getWidth()-1);
		pc_pos.y = rand.randInt(0, cave.getHeight()-1);
	} while(cave[pc_pos.x][pc_pos.y] != FloorTile);
	pm.setPosition(pc, pc_pos);
	sm.setSprite(pc, pc_sprite);

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

	//New set up our RenderSystem
	RenderSystem render(&level_window); //Be careful not to pass our viewport!

	wm.getWindow(0)->add(1, 0, "Message Panel");
	wm.getWindow(1)->add(1, 0, "Stat Panel");

	//Center the map viewport on the PC
	map.center(pc_pos.x, pc_pos.y);

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
	wm.getWindow(1)->addInt(4, 13, pc_pos.x);
	wm.getWindow(1)->add(1, 14, "Y:     ");
	wm.getWindow(1)->addInt(4, 14, pc_pos.y);

	//Find a random FloorTile to put our kobold on
	//int npc_x, npc_y;
	//Actor npc('k', "kobold", 0x00);
	//spawn_npc(npc, cave, npc_x, npc_y, pc_x, pc_y, 50);
	Entity kobold = em.createEntity();
	PositionComponent npc_pos;
	SpriteComponent npc_sprite = { 'k', 0, 0 };
	spawn_npc(cave, npc_pos, pc_pos, 35);
	pm.setPosition(kobold, npc_pos);
	sm.setSprite(kobold, npc_sprite);

	//Now display everything
	wm.getWindow(2)->loadLevel();
	render.execute(em);
	wm.refresh();

	//Now we enter the "game loop"
	int ch;
	int key_pos = 8;
	int last_key_pos;
	int dx, dy;
	int pc_dx, pc_dy;
	bool run = true;

	//Attack skills
	//Skill pc_atk;
	//pc_atk.setAttribute(&pc.getAttr(Str));
	//pc_atk.setRanks(13);

	//Defense skills
	Skill npc_dodge;
	npc_dodge.setRanks(10);

	while(run)
	{
		ch = getch();

		//Display the key code
		wm.getWindow(0)->add(key_pos, 1, "                                    ");
		wm.getWindow(0)->addInt(key_pos, 1, ch);

		dx = 0;
		dy = 0;
		pc_dx = 0;
		pc_dy = 0;

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
				pc_dx = 0;
				pc_dy = -1;
				break;
			case '2':
			case 'j':
				pc_dx = 0;
				pc_dy = 1;
				break;
			case '4':
			case 'h':
				pc_dx = -1;
				pc_dy = 0;
				break;
			case '6':
			case 'l':
				pc_dx = 1;
				pc_dy = 0;
				break;
			//Diagonal movement
			case '7':
			case 'y':
				pc_dx = -1;
				pc_dy = -1;
				break;
			case '9':
			case 'u':
				pc_dx = 1;
				pc_dy = -1;
				break;
			case '1':
			case 'b':
				pc_dx = -1;
				pc_dy = 1;
				break;
			case '3':
			case 'n':
				pc_dx = 1;
				pc_dy = 1;
				break;
			//Other commands
			case 'c':
			case 'C':
				//Center the view on the PC
				wm.getWindow(2)->center(pc_pos.x, pc_pos.y);
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

		//if(pc_dx != 0 || pc_dy != 0)
		//{
		//	//Test if the NPC is there
		//	if(cave[pc_x + pc_dx][pc_y + pc_dy].isOccupied())
		//	{
		//		//FIGHT!
		//		if(fight_npc(pc_atk, npc_dodge, wm.getWindow(0)))
		//		{
		//			//Kobold is dead, remove it from the map and spawn another
		//			cave[pc_x + pc_dx][pc_y + pc_dy].removeActor();
		//			spawn_npc(npc, cave, npc_x, npc_y, pc_x, pc_y);
		//		}
		//	} else {
		//		//Move the PC
		//		move_pc(pc, cave, pc_x, pc_y, pc_dx, pc_dy);
		//	}
		//}

		//Move the viewport
		map.moveBy(dx, dy);

		//Display our view's X and Y coordinates
		wm.getWindow(1)->add(1, 3, "X:     ");
		wm.getWindow(1)->addInt(4, 3, map.getViewX());
		wm.getWindow(1)->add(1, 4, "Y:     ");
		wm.getWindow(1)->addInt(4, 4, map.getViewY());

		//Re-display PC's position
		wm.getWindow(1)->add(1, 13, "X:     ");
		wm.getWindow(1)->addInt(4, 13, pc_pos.x);
		wm.getWindow(1)->add(1, 14, "Y:     ");
		wm.getWindow(1)->addInt(4, 14, pc_pos.y);

		//Display NPC's position
		//wm.getWindow(1)->add(1, 15, "NPC Position:");
		//wm.getWindow(1)->add(1, 16, "X:     ");
		//wm.getWindow(1)->addInt(4, 16, npc_x);
		//wm.getWindow(1)->add(1, 17, "Y:     ");
		//wm.getWindow(1)->addInt(4, 17, npc_y);

		//Refresh the display
		wm.getWindow(2)->loadLevel();
		render.execute(em);
		wm.refresh();
	}
}

#include <iostream>
#include <time.h>
#include <ncurses.h>

#include "display/Screen.h"
#include "map/Level.h"
#include "map/filters/FloodFillFilter.h"
#include "map/filters/DrunkardsWalkFilter.h"
#include "map/filters/BSPFilter.h"

int main()
{
	Screen screen;

	//std::cout << "Default Level:" << std::endl;
	printw("Default Level:");
	Level walls(40, 80);
	//walls.printLevel();
	for(uint32_t x = 0; x < walls.getWidth(); x++)
	{
		for(uint32_t y = 0; y < walls.getHeight(); y++)
		{
			mvaddch(x+1, y, walls[x][y].getDisplay());
		}
	}
	std::cout << std::endl << std::endl;
	refresh();
	getch();

	std::cout << "Flood-filled room:" << std::endl;
	Level room(40, 80);
	FloodFillFilter fill;
	fill.setStart(1,1);
	fill.setEnd(room.getWidth()-2, room.getHeight()-2);
	fill.setTile(FloorTile);
	fill.apply(room);
	room.printLevel();
	std::cout << std::endl << std::endl;

	std::cout << "A drunkard's walk cave:" << std::endl;
	Level cave(40, 80);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	cave.printLevel();
	std::cout << std::endl << std::endl;

	std::cout << "A BSP dungeon:" << std::endl;
	Level dungeon(40, 80);
	BSPFilter bsp;
	bsp.setSeed(time(NULL));
	bsp.apply(dungeon);
	dungeon.printLevel();
	std::cout << std::endl << std::endl;

	//std::cout << "DungeonBSPGenerator:" << std::endl;
	//DungeonBSPGenerator dungeon;
	//dungeon.setSeed(time(NULL));
	//Level ldungeon(40, 80);
	//ldungeon.printLevel();
	//std::cout << std::endl << std::endl;

	return 0;
}

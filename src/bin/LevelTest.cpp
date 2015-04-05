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

	printw("Default Level:");
	Level walls(40, 80);
	for(uint32_t x = 0; x < walls.getWidth(); x++)
	{
		for(uint32_t y = 0; y < walls.getHeight(); y++)
		{
			mvaddch(x+1, y, walls[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("Flood-filled room:");
	Level room(40, 80);
	FloodFillFilter fill;
	fill.setStart(1,1);
	fill.setEnd(room.getWidth()-2, room.getHeight()-2);
	fill.setTile(FloorTile);
	fill.apply(room);
	for(uint32_t x = 0; x < room.getWidth(); x++)
	{
		for(uint32_t y = 0; y < room.getHeight(); y++)
		{
			mvaddch(x+1, y, room[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("A drunkard's walk cave:");
	Level cave(40, 80);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	for(uint32_t x = 0; x < cave.getWidth(); x++)
	{
		for(uint32_t y = 0; y < cave.getHeight(); y++)
		{
			mvaddch(x+1, y, cave[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("A BSP dungeon:");
	Level dungeon(40, 80);
	BSPFilter bsp;
	bsp.setSeed(time(NULL));
	bsp.apply(dungeon);
	for(uint32_t x = 0; x < dungeon.getWidth(); x++)
	{
		for(uint32_t y = 0; y < dungeon.getHeight(); y++)
		{
			mvaddch(x+1, y, dungeon[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	return 0;
}

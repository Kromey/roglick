#include <time.h>
#include <ncurses.h>

#include "interface/Display.h"
#include "map/Map.h"
#include "map/filters/FloodFillFilter.h"
#include "map/filters/DrunkardsWalkFilter.h"
#include "map/filters/BSPFilter.h"

int main()
{
	Display disp;

	int width = disp.getScreenSize().y-2;
	int height = disp.getScreenSize().x-2;

	printw("Default Map:");
	Map walls(width, height);
	for(int x = 0; x < walls.getWidth(); x++)
	{
		for(int y = 0; y < walls.getHeight(); y++)
		{
			mvaddch(y+1, x, walls[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("Flood-filled room:");
	Map room(width, height);
	FloodFillFilter fill;
	fill.setRegion(1,1,room.getWidth()-2, room.getHeight()-2);
	fill.setTile(FloorTile);
	fill.apply(room);
	for(int x = 0; x < room.getWidth(); x++)
	{
		for(int y = 0; y < room.getHeight(); y++)
		{
			mvaddch(y+1, x, room[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("A drunkard's walk cave:");
	Map cave(width, height);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	for(int x = 0; x < cave.getWidth(); x++)
	{
		for(int y = 0; y < cave.getHeight(); y++)
		{
			mvaddch(y+1, x, cave[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	clear();
	printw("A BSP dungeon:");
	Map dungeon(width, height);
	BSPFilter bsp;
	bsp.setSeed(time(NULL));
	bsp.apply(dungeon);
	for(int x = 0; x < dungeon.getWidth(); x++)
	{
		for(int y = 0; y < dungeon.getHeight(); y++)
		{
			mvaddch(y+1, x, dungeon[x][y].getDisplay());
		}
	}
	refresh();
	getch();

	return 0;
}

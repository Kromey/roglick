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

	int width = screen.getWidth()-2;
	int height = screen.getHeight()-2;

	printw("Default Level:");
	Level walls(width, height);
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
	Level room(width, height);
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
	Level cave(width, height);
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
	Level dungeon(width, height);
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

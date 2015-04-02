#include <iostream>
#include <time.h>

#include "map/Level.h"
#include "map/filters/FloodFillFilter.h"
#include "map/filters/DrunkardsWalkFilter.h"

int main()
{
	std::cout << "Default Level:" << std::endl;
	Level walls(40, 80);
	walls.printLevel();
	std::cout << std::endl << std::endl;

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

	//std::cout << "DungeonBSPGenerator:" << std::endl;
	//DungeonBSPGenerator dungeon;
	//dungeon.setSeed(time(NULL));
	//Level ldungeon(40, 80);
	//ldungeon.printLevel();
	//std::cout << std::endl << std::endl;

	return 0;
}

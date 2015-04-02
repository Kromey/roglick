#include <iostream>
#include <time.h>

#include "map/Level.h"
#include "map/filters/FloodFillFilter.h"

int main()
{
	std::cout << "Default Level:" << std::endl;
	Level lwalls(40, 80);
	lwalls.printLevel();
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

	//std::cout << "CaveGenerator:" << std::endl;
	//CaveGenerator cave;
	//cave.setSeed(time(NULL));
	//Level lcave(40, 80);
	//lcave.printLevel();
	//std::cout << std::endl << std::endl;

	//std::cout << "DungeonBSPGenerator:" << std::endl;
	//DungeonBSPGenerator dungeon;
	//dungeon.setSeed(time(NULL));
	//Level ldungeon(40, 80);
	//ldungeon.printLevel();
	//std::cout << std::endl << std::endl;

	return 0;
}

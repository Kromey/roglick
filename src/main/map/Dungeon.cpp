#include "map/Dungeon.h"
#include "map/filters/DrunkardsWalkFilter.h"

Dungeon::Dungeon() : _type(Cave), _level(NULL)
{
	//Start out on level 1
	changeDungeonLevel(1);
}

Dungeon::Dungeon(dungeon_t type) : _type(type), _level(NULL)
{
	//Start out on level 1
	changeDungeonLevel(1);
}

void Dungeon::changeDungeonLevel(int new_level)
{
	if(_current_level != new_level)
	{
		_current_level = new_level;

		generateDungeonMap();
	}
}

void Dungeon::generateDungeonMap()
{
	///@todo Don't hard-code map dimensions
	int map_x = 150;
	int map_y = 150;

	if(NULL != _level)
	{
		delete _level;
	}

	switch(_type)
	{
		case Cave:
			//Use a block so we can initialize variables in our case
			{
				//Generate a map
				_level = new Level(map_x, map_y);
				DrunkardsWalkFilter walk;
				walk.setSeed(time(NULL));
				walk.apply(*_level);
			}
			break;

		//case Dungeon:
		case City:
		case Camp:
		case Wilderness:
			//Un-implemented Dungeon type, change to cave and start over
			_type = Cave;
			generateDungeonMap();
			break;
	}
}


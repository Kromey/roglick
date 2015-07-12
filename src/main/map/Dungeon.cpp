#include "map/Dungeon.h"
#include "map/filters/DrunkardsWalkFilter.h"

Dungeon::Dungeon() : _type(CaveDungeon), _level(NULL)
{
	//Start out on level 1
	changeDungeonLevel(1);

	//An almost-random default seed
	_seed = time(NULL);
}

Dungeon::Dungeon(dungeon_t type) : _type(type), _level(NULL)
{
	//Start out on level 1
	changeDungeonLevel(1);

	//An almost-random default seed
	_seed = time(NULL);
}

uint32_t Dungeon::getDungeonSeed()
{
	return _seed;
}

void Dungeon::setDungeonSeed(uint32_t seed)
{
	_seed = seed;
}

void Dungeon::changeDungeonLevel(int new_level)
{
	if(_current_level != new_level)
	{
		_current_level = new_level;

		if(NULL != _level)
		{
			delete _level;
			_level = NULL;
		}
	}
}

Level* Dungeon::getLevel()
{
	if(NULL == _level)
	{
		generateDungeonMap();
	}

	return _level;
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
		case CaveDungeon:
			//Use a block so we can initialize variables in our case
			{
				//Generate a map
				_level = new Level(map_x, map_y);
				DrunkardsWalkFilter walk;
				walk.setSeed(getLevelSeed());
				walk.apply(*_level);
			}
			break;

		case DungeonDungeon:
		case CityDungeon:
		case CampDungeon:
		case WildernessDungeon:
			//Un-implemented Dungeon type, change to cave and start over
			_type = CaveDungeon;
			generateDungeonMap();
			break;
	}
}

uint32_t Dungeon::getLevelSeed()
{
	return _seed + _current_level;
}


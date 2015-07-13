#include "map/Dungeon.h"
#include "map/filters/DrunkardsWalkFilter.h"

Dungeon::Dungeon() : _type(CaveDungeon), _map(NULL)
{
	//Start out on level 1
	changeDungeonLevel(1);

	//An almost-random default seed
	_seed = time(NULL);
}

Dungeon::Dungeon(dungeon_t type) : _type(type), _map(NULL)
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

		if(NULL != _map)
		{
			delete _map;
			_map = NULL;
		}
	}
}

Map* Dungeon::getMap()
{
	if(NULL == _map)
	{
		generateDungeonMap();
	}

	return _map;
}

void Dungeon::generateDungeonMap()
{
	///@todo Don't hard-code map dimensions
	int map_x = 150;
	int map_y = 150;

	if(NULL != _map)
	{
		delete _map;
	}

	switch(_type)
	{
		case CaveDungeon:
			//Use a block so we can initialize variables in our case
			{
				//Generate a map
				_map = new Map(map_x, map_y);
				DrunkardsWalkFilter walk;
				walk.setSeed(getMapSeed());
				walk.apply(*_map);
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

uint32_t Dungeon::getMapSeed()
{
	///@todo I don't like this, I'd prefer a method that results in much more
	///variance of the seed.
	return _seed + _current_level;
}


#include <iostream>

#include "map/generators/DungeonBSPGenerator.h"
#include "map/generators/WallsGenerator.h"
#include "core/Rand.h"

DungeonBSPGenerator::DungeonBSPGenerator(uint32_t splits)
{
	_splits = splits;
}

void DungeonBSPGenerator::generateMap(uint32_t width, uint32_t height, Tile** tiles)
{
	//First we start with solid walls.
	WallsGenerator wall_gen;
	wall_gen.generateMap(width, height, tiles);

	Rand rand(_seed);

	splitTheDungeon(0, 0, width, height, _splits-1, rand, tiles);
}

void DungeonBSPGenerator::splitTheDungeon(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t splits, Rand& rand, Tile** tiles)
{
	if(0 < splits)
	{
		if(0 == rand.randBit())
		{
			//Splitting the x axis
			uint32_t new_x = rand.randInt(x1 * 1.2, x2 * 0.8);

			splitTheDungeon(x1, y1, new_x, y2, splits-1, rand, tiles);
			splitTheDungeon(new_x, y1, x2, y2, splits-1, rand, tiles);
		} else {
			//Splitting the x axis
			uint32_t new_y = rand.randInt(y1 * 1.2, y2 * 0.8);

			splitTheDungeon(x1, y1, x2, new_y, splits-1, rand, tiles);
			splitTheDungeon(x1, new_y, x2, y2, splits-1, rand, tiles);
		}
	} else {
		//Put a room in here
		for(uint32_t x = x1 + 1; x < x2 - 1; x++)
		{
			for(uint32_t y = y1 + 1; y < y2 - 1; y++)
			{
				tiles[x][y] = FloorTile;
			}
		}
	}
}

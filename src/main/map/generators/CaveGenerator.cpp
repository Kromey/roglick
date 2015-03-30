#include "map/generators/CaveGenerator.h"
#include "map/generators/WallsGenerator.h"
#include "core/Rand.h"

CaveGenerator::CaveGenerator(float cave_ratio)
{
	_cave_ratio = cave_ratio;
}

void CaveGenerator::generateMap(uint32_t width, uint32_t height, Tile** tiles)
{
	//First we start with solid walls.
	WallsGenerator wall_gen;
	wall_gen.generateMap(width, height, tiles);

	//Now we keep track of how many floor tiles we've carved out.
	uint32_t floor_count = 0;
	uint32_t max_floors = (width * height) * _cave_ratio;

	//This will let us do the comparisons.
	Tile wall = WallTile;

	//Need a random generator
	Rand rand(_seed);

	//Start at random x,y, but avoid the perimeter
	uint32_t x = rand.randInt(1, width-2);
	uint32_t y = rand.randInt(1, height-2);
	uint32_t dx;
	uint32_t dy;

	while(floor_count < max_floors)
	{
		if(tiles[x][y] == wall)
		{
			tiles[x][y] = FloorTile;
			floor_count++;
		}

		do {
			dx = rand.randInt(2) - 1;
			dy = rand.randInt(2) - 1;
		} while(
			x + dx <= 0 || x + dx >= width  - 1 ||
			y + dy <= 0 || y + dy >= height - 1
			);

		x += dx;
		y += dy;
	}
}

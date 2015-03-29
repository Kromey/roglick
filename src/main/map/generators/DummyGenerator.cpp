#include "map/generators/DummyGenerator.h"

//Simplify the signatures.
using namespace map;

void DummyGenerator::generateMap(uint32_t width, uint32_t height, Tile** tiles)
{
	for(uint32_t x = 0; x < width; x++)
	{
		for(uint32_t y = 0; y < height; y++)
		{
			tiles[x][y] = WallTile;
		}
	}
}

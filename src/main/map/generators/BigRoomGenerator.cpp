#include "map/generators/BigRoomGenerator.h"

void BigRoomGenerator::generateMap(uint32_t width, uint32_t height, Tile** tiles)
{
	for(uint32_t x = 0; x < width; x++)
	{
		for(uint32_t y = 0; y < height; y++)
		{
			if(x > 0 && x < width-1 && y > 0 && y < height-1)
			{
				tiles[x][y] = FloorTile;
			} else {
				tiles[x][y] = WallTile;
			}
		}
	}
}

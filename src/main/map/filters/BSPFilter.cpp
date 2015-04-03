#include <iostream>

#include "map/filters/BSPFilter.h"
#include "core/Rand.h"

BSPFilter::BSPFilter()
{
	_splits = 4;
}

void BSPFilter::setSplits(uint32_t splits)
{
	_splits = splits;
}

void BSPFilter::apply(Level& level)
{
	Rand rand(_seed);

	splitLevel(0, 0, level.getWidth(), level.getHeight(), _splits-1, rand, level);
}

void BSPFilter::splitLevel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t splits, Rand& rand, Level& level)
{
	if(0 < splits)
	{
		if(0 == rand.randBit())
		{
			//Splitting the x axis
			uint32_t new_x = rand.randInt(x1 * 1.2, x2 * 0.8);

			splitLevel(x1, y1, new_x, y2, splits-1, rand, level);
			splitLevel(new_x, y1, x2, y2, splits-1, rand, level);
		} else {
			//Splitting the x axis
			uint32_t new_y = rand.randInt(y1 * 1.2, y2 * 0.8);

			splitLevel(x1, y1, x2, new_y, splits-1, rand, level);
			splitLevel(x1, new_y, x2, y2, splits-1, rand, level);
		}
	} else {
		//Put a room in here
		for(uint32_t x = x1 + 1; x < x2 - 1; x++)
		{
			for(uint32_t y = y1 + 1; y < y2 - 1; y++)
			{
				level.setTile(x, y, FloorTile);
			}
		}
	}
}

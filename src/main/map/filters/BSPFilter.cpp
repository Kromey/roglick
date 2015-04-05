#include <iostream>

#include "map/filters/BSPFilter.h"
#include "core/Rand.h"

BSPFilter::BSPFilter()
{
	_partitions = 4;
}

void BSPFilter::setPartitions(uint32_t partitions)
{
	_partitions = partitions;
}

void BSPFilter::apply(Level& level)
{
	Rand rand(_seed);

	partitionLevel(0, 0, level.getWidth(), level.getHeight(), _partitions-1, rand, level);
}

void BSPFilter::partitionLevel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t partitions, Rand& rand, Level& level)
{
	if(0 < partitions)
	{
		if(0 == rand.randBit())
		{
			//Splitting the x axis
			uint32_t margin = (x2 - x1) * 0.2;
			uint32_t new_x = rand.randInt(x1 + margin, x2 - margin);

			partitionLevel(x1, y1, new_x, y2, partitions-1, rand, level);
			partitionLevel(new_x, y1, x2, y2, partitions-1, rand, level);
		} else {
			//Splitting the y axis
			uint32_t margin = (y2 - y1) * 0.2;
			uint32_t new_y = rand.randInt(y1 + margin, y2 - margin);

			partitionLevel(x1, y1, x2, new_y, partitions-1, rand, level);
			partitionLevel(x1, new_y, x2, y2, partitions-1, rand, level);
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

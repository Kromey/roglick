#include <iostream>

#include "map/filters/BSPFilter.h"
#include "core/Rand.h"

BSPFilter::BSPFilter()
{
	_min_partition = 10;

	_filler.setTile(FloorTile);
}

void BSPFilter::setMinPartition(uint32_t min_partition)
{
	_min_partition = min_partition;
}

void BSPFilter::apply(Level& level)
{
	Rand rand(_seed);

	partitionLevel(0, 0, level.getWidth(), level.getHeight(), rand, level);
}

void BSPFilter::partitionLevel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Rand& rand, Level& level, uint32_t retries)
{
	if(0 == rand.randBit())
	{
		//Splitting the x axis
		uint32_t margin = (x2 - x1) * 0.2;
		uint32_t new_x = rand.randInt(x1 + margin, x2 - margin);

		if(_min_partition < new_x - x1 && _min_partition < x2 - new_x)
		{
			//Partition the level to the new size
			partitionLevel(x1, y1, new_x, y2, rand, level);
			partitionLevel(new_x, y1, x2, y2, rand, level);
		} else if(retries > 0) {
			//We've got retries left, so retry
			partitionLevel(x1, y1, x2, y2, rand, level, retries-1);
		} else {
			//Put a room in here
			makeRoom(x1, y1, x2, y2, rand, level);
		}
	} else {
		//Splitting the y axis
		uint32_t margin = (y2 - y1) * 0.2;
		uint32_t new_y = rand.randInt(y1 + margin, y2 - margin);

		if(_min_partition < new_y - y1 && _min_partition < y2 - new_y)
		{
			//Partition the level to the new size
			partitionLevel(x1, y1, x2, new_y, rand, level);
			partitionLevel(x1, new_y, x2, y2, rand, level);
		} else if(retries > 0) {
			//We've got retries left, so retry
			partitionLevel(x1, y1, x2, y2, rand, level, retries-1);
		} else {
			//Put a room in here
			makeRoom(x1, y1, x2, y2, rand, level);
		}
	}
}

void BSPFilter::makeRoom(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Rand& rand, Level& level)
{
	//Find our midpoints
	uint32_t mid_x = (x1 + x2) / 2;
	uint32_t mid_y = (y1 + y2) / 2;

	//Pick a random spot on either half
	uint32_t room_x1 = rand.randInt(x1, mid_x);
	uint32_t room_x2 = rand.randInt(mid_x, x2);

	//...and same thing on the y axis
	uint32_t room_y1 = rand.randInt(y1, mid_y);
	uint32_t room_y2 = rand.randInt(mid_y, y2);

	//Now use our FloodFillFilter to put a room here
	_filler.setRegion(room_x1, room_y1, room_x2, room_y2);
	_filler.apply(level);
}


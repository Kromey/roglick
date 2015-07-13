#include <iostream>

#include "map/filters/BSPFilter.h"
#include "core/Rand.h"

BSPFilter::BSPFilter()
{
	_min_partition = 10;

	_filler.setTile(FloorTile);
}

void BSPFilter::setMinPartition(int min_partition)
{
	_min_partition = min_partition;
}

void BSPFilter::apply(Map& map)
{
	Rand rand(_seed);

	partitionMap(0, 0, map.getWidth(), map.getHeight(), rand, map);
}

void BSPFilter::partitionMap(int x1, int y1, int x2, int y2, Rand& rand, Map& map, int retries)
{
	if(0 == rand.randBit())
	{
		//Splitting the x axis
		int margin = (x2 - x1) * 0.2;
		int new_x = rand.randInt(x1 + margin, x2 - margin);

		if(_min_partition < new_x - x1 && _min_partition < x2 - new_x)
		{
			//Partition the map to the new size
			partitionMap(x1, y1, new_x, y2, rand, map);
			partitionMap(new_x, y1, x2, y2, rand, map);
		} else if(retries > 0) {
			//We've got retries left, so retry
			partitionMap(x1, y1, x2, y2, rand, map, retries-1);
		} else {
			//Put a room in here
			makeRoom(x1, y1, x2, y2, rand, map);
		}
	} else {
		//Splitting the y axis
		int margin = (y2 - y1) * 0.2;
		int new_y = rand.randInt(y1 + margin, y2 - margin);

		if(_min_partition < new_y - y1 && _min_partition < y2 - new_y)
		{
			//Partition the map to the new size
			partitionMap(x1, y1, x2, new_y, rand, map);
			partitionMap(x1, new_y, x2, y2, rand, map);
		} else if(retries > 0) {
			//We've got retries left, so retry
			partitionMap(x1, y1, x2, y2, rand, map, retries-1);
		} else {
			//Put a room in here
			makeRoom(x1, y1, x2, y2, rand, map);
		}
	}
}

void BSPFilter::makeRoom(int x1, int y1, int x2, int y2, Rand& rand, Map& map)
{
	//Find our midpoints
	int mid_x = (x1 + x2) / 2;
	int mid_y = (y1 + y2) / 2;

	//Pick a random spot on either half
	int room_x1 = rand.randInt(x1, mid_x);
	int room_x2 = rand.randInt(mid_x, x2);

	//Reselect if we picked one of our boundaries
	if(x1 == room_x1)
	{
		room_x1 = rand.randInt(x1, mid_x);
	}
	if(x2 == room_x2)
	{
		room_x2 = rand.randInt(mid_x, x2);
	}

	//...and same thing on the y axis
	int room_y1 = rand.randInt(y1, mid_y);
	int room_y2 = rand.randInt(mid_y, y2);

	//Reselect if we picked one of our boundaries
	if(y1 == room_y1)
	{
		room_y1 = rand.randInt(y1, mid_y);
	}
	if(y2 == room_y2)
	{
		room_y2 = rand.randInt(mid_y, y2);
	}

	//Now use our FloodFillFilter to put a room here
	_filler.setRegion(room_x1, room_y1, room_x2, room_y2);
	_filler.apply(map);
}


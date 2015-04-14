#include <stdexcept>

#include "map/filters/FloodFillFilter.h"

FloodFillFilter::FloodFillFilter()
{
	_x1 = 0;
	_y1 = 0;

	_x2 = 0;
	_y2 = 0;

	_constrain_region = false;

	_tile = WallTile;
}

void FloodFillFilter::apply(Level& level)
{
	if(false == _constrain_region)
	{
		//No region set, so we'll cover the whole level
		_x2 = level.getWidth() - 1;
		_y2 = level.getHeight() - 1;
	}

	if(_x1 > _x2 || _y1 > _y2)
	{
		throw std::out_of_range("Start coordinates cannot exceed end coordinates");
	}

	if(_x1 >= level.getWidth())
	{
		_x1 = level.getWidth() - 1;
	}
	if(_x2 >= level.getWidth())
	{
		_x2 = level.getWidth() - 1;
	}
	if(_y1 >= level.getHeight())
	{
		_y1 = level.getHeight() - 1;
	}
	if(_y2 >= level.getHeight())
	{
		_y2 = level.getHeight() - 1;
	}

	for(int x = _x1; x <= _x2; x++)
	{
		for(int y = _y1; y <= _y2; y++)
		{
			level.setTile(x, y, _tile);
		}
	}
}

void FloodFillFilter::setRegion(int x1, int y1, int x2, int y2)
{
	_x1 = x1;
	_y1 = y1;

	_x2 = x2;
	_y2 = y2;

	_constrain_region = true;
}

void FloodFillFilter::setTile(Tile tile)
{
	_tile = tile;
}

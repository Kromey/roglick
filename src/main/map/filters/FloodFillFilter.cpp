#include <stdexcept>

#include "map/filters/FloodFillFilter.h"

FloodFillFilter::FloodFillFilter()
{
	_x1 = 0;
	_y1 = 0;

	_x2 = LEVEL_MAX_WIDTH;
	_y2 = LEVEL_MAX_HEIGHT;

	_tile = WallTile;
}

void FloodFillFilter::apply(Level& level)
{
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

	for(uint32_t x = _x1; x <= _x2; x++)
	{
		for(uint32_t y = _y1; y <= _y2; y++)
		{
			level.setTile(x, y, _tile);
		}
	}
}

void FloodFillFilter::setStart(uint32_t x, uint32_t y)
{
	_x1 = x;
	_y1 = y;
}

void FloodFillFilter::setEnd(uint32_t x, uint32_t y)
{
	_x2 = x;
	_y2 = y;
}

void FloodFillFilter::setTile(Tile tile)
{
	_tile = tile;
}

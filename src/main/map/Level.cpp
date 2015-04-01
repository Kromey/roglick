#include <iostream>
#include <stdexcept>

#include "map/Level.h"

Level::Level(uint32_t width, uint32_t height)
{
	_width = width;
	_height = height;

	initializeLevel();
}

Level::~Level()
{
	//Delete each column...
	for(uint32_t i = 0; i < _width; i++)
	{
		delete [] _tiles[i];
	}
	//...then delete the storage of the columns themselves
	delete [] _tiles;
}

void Level::printLevel()
{
	for(uint32_t x = 0; x < _width; x++)
	{
		for(uint32_t y = 0; y < _height; y++)
		{
			std::cout << getTile(x, y).getDisplay();
		}
		std::cout << std::endl;
	}
}

Tile& Level::getTile(uint32_t x, uint32_t y)
{
	//uints are always positive, only have to check upper bounds
	if(x < _width && y < _height)
	{
		return _tiles[x][y];
	} else {
		throw std::out_of_range("Cannot access Tile outside of Level boundaries");
	}
}

//Nothing to do except initialize our internal members.
Level::Proxy::Proxy(Level& level, uint32_t x) : _level(level), _x(x) {}

//Retrieve the proxied x and specified y coordinates.
Tile& Level::Proxy::operator[](uint32_t y)
{
	return _level.getTile(_x, y);
}

//Proxy this x coordinate via our Proxy object.
Level::Proxy Level::operator[](uint32_t x)
{
	return Proxy(*this, x);
}

void Level::initializeLevel()
{
	_tiles = new Tile*[_width];
	for(uint32_t i = 0; i < _width; i++)
	{
		_tiles[i] = new Tile[_height];
	}
}


#include <iostream>
#include <stdexcept>

#include "map/Level.h"

Level::Level(int width, int height)
{
	_width = width;
	_height = height;

	initializeLevel();
}

Level::~Level()
{
	//Delete each column...
	for(int i = 0; i < _width; i++)
	{
		delete [] _tiles[i];
	}
	//...then delete the storage of the columns themselves
	delete [] _tiles;
}

void Level::printLevel()
{
	for(int y = 0; y < _height; y++)
	{
		for(int x = 0; x < _width; x++)
		{
			std::cout << getTile(x, y).getDisplay();
		}
		std::cout << std::endl;
	}
}

int Level::getWidth()
{
	return _width;
}

int Level::getHeight()
{
	return _height;
}

Tile& Level::getTile(int x, int y)
{
	if(0 <= x && 0 <= y && x < _width && y < _height)
	{
		return _tiles[x][y];
	} else {
		throw std::out_of_range("Cannot access Tile outside of Level boundaries");
	}
}

void Level::setTile(int x, int y, Tile tile)
{
	if(0 <= x && 0 <= y && x < _width && y < _height)
	{
		_tiles[x][y] = tile;
	} else {
		throw std::out_of_range("Cannot access Tile outside of Level boundaries");
	}
}

//Nothing to do except initialize our internal members.
Level::Proxy::Proxy(Level& level, int x) : _level(level), _x(x) {}

//Retrieve the proxied x and specified y coordinates.
Tile& Level::Proxy::operator[](int y)
{
	return _level.getTile(_x, y);
}

//Proxy this x coordinate via our Proxy object.
Level::Proxy Level::operator[](int x)
{
	return Proxy(*this, x);
}

void Level::initializeLevel()
{
	_tiles = new Tile*[_width];
	for(int i = 0; i < _width; i++)
	{
		_tiles[i] = new Tile[_height];
	}
}


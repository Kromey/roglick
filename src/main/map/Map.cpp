#include <iostream>
#include <stdexcept>

#include "map/Map.h"

Map::Map(int width, int height)
{
	_width = width;
	_height = height;

	initializeMap();
}

Map::~Map()
{
	//Delete each column...
	for(int i = 0; i < _width; i++)
	{
		delete [] _tiles[i];
	}
	//...then delete the storage of the columns themselves
	delete [] _tiles;
}

void Map::printMap()
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

int Map::getWidth()
{
	return _width;
}

int Map::getHeight()
{
	return _height;
}

Tile& Map::getTile(int x, int y)
{
	if(0 <= x && 0 <= y && x < _width && y < _height)
	{
		return _tiles[x][y];
	} else {
		throw std::out_of_range("Cannot access Tile outside of Map boundaries");
	}
}

void Map::setTile(int x, int y, Tile tile)
{
	if(0 <= x && 0 <= y && x < _width && y < _height)
	{
		_tiles[x][y] = tile;
	} else {
		throw std::out_of_range("Cannot access Tile outside of Map boundaries");
	}
}

//Nothing to do except initialize our internal members.
Map::Proxy::Proxy(Map& map, int x) : _map(map), _x(x) {}

//Retrieve the proxied x and specified y coordinates.
Tile& Map::Proxy::operator[](int y)
{
	return _map.getTile(_x, y);
}

//Proxy this x coordinate via our Proxy object.
Map::Proxy Map::operator[](int x)
{
	return Proxy(*this, x);
}

void Map::initializeMap()
{
	_tiles = new Tile*[_width];
	for(int i = 0; i < _width; i++)
	{
		_tiles[i] = new Tile[_height];
	}
}


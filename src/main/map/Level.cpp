#include <iostream>

#include "map/Level.h"

Level::Level(uint32_t width, uint32_t height, Generator& level_generator)
{
	_width = width;
	_height = height;

	initializeLevel();

	level_generator.generateMap(_width, _height, _tiles);
}

/**
 * @fixme Need to delete the dynamically-allocated space
 */
Level::~Level()
{
}

void Level::printLevel()
{
	for(uint32_t x = 0; x < _width; x++)
	{
		for(uint32_t y = 0; y < _height; y++)
		{
			std::cout << _tiles[x][y].getDisplay();
		}
		std::cout << std::endl;
	}
}

void Level::initializeLevel()
{
	_tiles = new Tile*[_width];
	for(uint32_t i = 0; i < _width; i++)
	{
		_tiles[i] = new Tile[_height];
	}
}


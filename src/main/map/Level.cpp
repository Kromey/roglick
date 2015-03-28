#include "map/Level.h"

//Simplify the upcoming definitions.
using namespace map;

Level::Level(uint32_t width, uint32_t height, Generator& level_generator)
{
	_width = width;
	_height = height;

	level_generator.generateMap(_width, _height, _tiles);
}

Level::~Level()
{
}


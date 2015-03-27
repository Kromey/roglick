#include "map/Tile.h"

//Simplify the upcoming definitions.
using namespace map;

//Default constructor
Tile::Tile()
{
	//Default to solid walls
	setTransparent(false);
	setPassable(false);
}

bool Tile::getTransparent()
{
	return _isTransparent;
}

void Tile::setTransparent(bool isTransparent)
{
	_isTransparent = isTransparent;
}

bool Tile::getPassable()
{
	return _isPassable;
}

void Tile::setPassable(bool isPassable)
{
	_isPassable = isPassable;
}


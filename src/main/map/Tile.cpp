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
	return getBit(Tile::ISTRANSPARENT);
}

void Tile::setTransparent(bool isTransparent)
{
	setBit(Tile::ISTRANSPARENT, isTransparent);
}

bool Tile::getPassable()
{
	return getBit(Tile::ISPASSABLE);
}

void Tile::setPassable(bool isPassable)
{
	setBit(Tile::ISPASSABLE, isPassable);
}

bool Tile::getBit(uint32_t pos)
{
	return ((_flags >> pos) & 0x01) == 0x01;
}

void Tile::setBit(uint32_t pos, bool value)
{
	if(value)
	{
		_flags |= 0x01 << pos;
	} else {
		_flags &= ~(0x01 << pos);
	}
}


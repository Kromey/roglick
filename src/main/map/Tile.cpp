#include "map/Tile.h"

//Simplify the upcoming definitions.
using namespace map;

//Default constructor
Tile::Tile()
{
	//Create a WallTile
	*this = WallTile;
}

//Constructor
Tile::Tile(char display, std::string name, uint32_t flags)
{
	//Assign our internal values
	_display = display;
	_name = name;
	_flags = flags;
}

bool Tile::getTransparent() const
{
	return getBit(Tile::ISTRANSPARENT);
}

void Tile::setTransparent(bool isTransparent)
{
	setBit(Tile::ISTRANSPARENT, isTransparent);
}

bool Tile::getPassable() const
{
	return getBit(Tile::ISPASSABLE);
}

void Tile::setPassable(bool isPassable)
{
	setBit(Tile::ISPASSABLE, isPassable);
}

bool Tile::getBit(uint32_t pos) const
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


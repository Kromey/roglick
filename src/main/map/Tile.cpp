#include "map/Tile.h"

//Default constructor
Tile::Tile()
{
	//Create a WallTile
	*this = WallTile;
}

//Constructor
Tile::Tile(char display, std::string name, int flags) : _flags(flags)
{
	//Assign our internal values
	_display = display;
	_name = name;

	_actor = NULL;
}

bool Tile::operator==(const Tile& rhs) const
{
	return _display == rhs._display && _flags == rhs._flags;
}

bool Tile::operator!=(const Tile& rhs) const
{
	return !operator==(rhs);
}

bool Tile::isTransparent() const
{
	return getBit(Tile::ISTRANSPARENT);
}

void Tile::setTransparent(bool is_transparent)
{
	setBit(Tile::ISTRANSPARENT, is_transparent);
}

bool Tile::isPassable() const
{
	return getBit(Tile::ISPASSABLE);
}

void Tile::setPassable(bool is_passable)
{
	setBit(Tile::ISPASSABLE, is_passable);
}

char Tile::getDisplay()
{
	if(NULL == _actor)
	{
		return _display;
	} else {
		return _actor->getDisplay();
	}
}

void Tile::addActor(Actor* actor)
{
	_actor = actor;
}

bool Tile::isOccupied()
{
	//A simple matter of true if _actor isn't NULL
	return NULL != _actor;
}

void Tile::removeActor()
{
	_actor = NULL;
}

bool Tile::getBit(int pos) const
{
	return _flags[pos];
}

void Tile::setBit(int pos, bool value)
{
	_flags[pos] = value;
}


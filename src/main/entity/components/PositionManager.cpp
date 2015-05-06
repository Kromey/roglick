#include <cstddef>

#include "entity/components/PositionManager.h"

#define MAPBUFFER 5
#define NOVAL -1

bool operator==(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//A position is the same if x1==x2 and y1==y2, but this is so obvious I
	//really don't know why I'm writing a comment to tell you that...
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//No reason to duplicate code, just invert the equality operator!
	return !(lhs == rhs);
}

const PositionComponent PositionManager::NULL_POS = { -1, -1 };

PositionManager::PositionManager() : _entity_map(MAPBUFFER, NOVAL)
{
}

bool PositionManager::entityHasComponent(Entity e)
{
	if(e >= _entity_map.size() || NOVAL == _entity_map[e])
	{
		return false;
	} else {
		return true;
	}
}

void PositionManager::addComponent(Entity e)
{
	//Add default PositionComponent to our list of Components
	setPosition(e, NULL_POS);
}

void PositionManager::removeComponent(Entity e)
{
	int idx = _entity_map[e];

	//Set our map to reflect that this Entity no longer has a position
	_entity_map[e] = NOVAL;

	//Find the largest index in our entity_map
	int max_idx = idx;
	Entity max_e = e;
	for(unsigned int i = 0; i < _entity_map.size(); i++)
	{
		if(_entity_map[i] > max_idx)
		{
			max_idx = _entity_map[i];
			max_e = i;
		}
	}

	if(max_idx != idx)
	{
		//Fill the new gap with our current last component
		_positions[idx] = _positions[max_idx];
		_entity_map[max_e] = idx;

		//Now shrink our vector to fit our new size
		_positions.resize(_positions.size() - 1);
	}
}

PositionComponent PositionManager::getPosition(Entity e)
{
	if(entityHasComponent(e))
	{
		//Look up where the Entity's position is kept...
		int idx = _entity_map[e];
		//...and fetch it
		return _positions[idx];
	} else {
		//Entity has no position
		return NULL_POS;
	}
}

void PositionManager::setPosition(Entity e, PositionComponent pos)
{
	if(entityHasComponent(e))
	{
		int idx = _entity_map[e];
		_positions[idx] = pos;
	} else {
		//Brand spankin' new PositionComponent
		//Add this to our vector of positions
		_positions.push_back(pos);

		//Make sure we have room in our Entity map
		if(_entity_map.size() <= e)
		{
			_entity_map.resize(e+MAPBUFFER, NOVAL);
		}

		//Now update our Entity map; we just added the Component to the end
		_entity_map[e] = _positions.size()-1;
	}
}

int PositionManager::getX(Entity e)
{
	//Get the Entity's position and return the X component
	return getPosition(e).x;
}

void PositionManager::setX(Entity e, int x)
{
	//Get the current position
	PositionComponent pos = getPosition(e);

	//Update the X coordinate
	pos.x = x;

	//Set the new position
	setPosition(e, pos);
}

int PositionManager::getY(Entity e)
{
	//Get the Entity's position and return the Y component
	return getPosition(e).y;
}

void PositionManager::setY(Entity e, int y)
{
	//Get the current position
	PositionComponent pos = getPosition(e);

	//Update the Y coordinate
	pos.y = y;

	//Set the new position
	setPosition(e, pos);
}

Entity PositionManager::getEntityAtPosition(PositionComponent pos)
{
	//Scour our Entity positions for a matching position
	int idx;
	for(Entity i = 0; i < _entity_map.size(); i++)
	{
		idx = _entity_map[i];
		if(idx != NOVAL)
		{
			if(pos == _positions[idx])
			{
				return i;
			}
		}
	}

	/// @bug Need something better than this return value! In fact, this is not
	/// only a poor handling of the default case, it is also **extremely
	/// dangerous** because 0 is a valid Entity!
	return 0;
}

Entity PositionManager::getEntityAtPosition(int x, int y)
{
	//Build a PositionComponent from our x,y
	PositionComponent pos = { x, y };
	//Now use that in our already-written method
	return getEntityAtPosition(pos);
}


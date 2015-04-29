#include <cstddef>

#include "entity/components/PositionManager.h"

#define MAPBUFFER 5
#define NOVAL -1

PositionComponent::PositionComponent() : _x(0), _y(0)
{
}

PositionComponent::PositionComponent(int x, int y) : _x(x), _y(y)
{
}

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

void PositionManager::addComponent(Entity e, Component* c)
{
	//Add the Component to our list of Components
	PositionComponent* p = (PositionComponent*)c;
	_positions.push_back(*p);

	//Make sure we have room in our Entity map
	if(_entity_map.size() <= e)
	{
		_entity_map.resize(e+MAPBUFFER, NOVAL);
	}

	//Now update our Entity map; we just added the Component to the end
	_entity_map[e] = _positions.size()-1;
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

Component* PositionManager::getComponent(Entity e)
{
	if(entityHasComponent(e))
	{
		int idx = _entity_map[e];
		return &(_positions[idx]);
	} else {
		return NULL;
	}
}


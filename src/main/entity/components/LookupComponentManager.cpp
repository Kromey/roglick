#include "entity/components/LookupComponentManager.h"

#define MAPBUFFER 5
#define NOVAL -1

LookupComponentManager::LookupComponentManager() : _entity_map(MAPBUFFER, NOVAL)
{
}

bool LookupComponentManager::entityHasComponent(Entity e)
{
	if(e >= _entity_map.size() || NOVAL == _entity_map[e])
	{
		return false;
	} else {
		return true;
	}
}

int LookupComponentManager::addComponentIndex(Entity e)
{
	if(entityHasComponent(e))
	{
		//int idx = _entity_map[e];
		//_positions[idx] = pos;
	} else {
		//Brand spankin' new PositionComponent
		//Add this to our vector of positions
		//_positions.push_back(pos);

		//Make sure we have room in our Entity map
		if(_entity_map.size() <= e)
		{
			_entity_map.resize(e+MAPBUFFER, NOVAL);
		}

		//Now update our Entity map; we just added the Component to the end
		//_entity_map[e] = _positions.size()-1;
	}

	return _entity_map[e];
}

int LookupComponentManager::getComponentIndex(Entity e)
{
	return _entity_map[e];
}

void LookupComponentManager::setComponentIndex(Entity e, int idx)
{
	_entity_map[e] = idx;
}

void LookupComponentManager::getMaxComponentIndex(Entity& e, int& idx)
{
	for(unsigned int i = 0; i < _entity_map.size(); i++)
	{
		if(_entity_map[i] > idx)
		{
			idx = _entity_map[i];
			e = i;
		}
	}
}


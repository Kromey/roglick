#include "entity/components/LookupComponentManager.h"

#define MAPBUFFER 5
#define NOVAL -1

bool LookupComponentManager::entityHasComponent(Entity e)
{
	if(NULL_ENTITY == e || e >= _entity_map.size() || NOVAL == _entity_map[e])
	{
		return false;
	} else {
		return true;
	}
}

int LookupComponentManager::getComponentIndex(Entity e)
{
	if(entityHasComponent(e))
	{
		//The Entity's component index
		return _entity_map[e];
	} else {
		//No index
		return NOVAL;
	}
}

void LookupComponentManager::setComponentIndex(Entity e, int idx)
{
	if(NULL_ENTITY == e)
	{
		//Do nothing for a nothing Entity
		return;
	}

	//Make sure we have room in our Entity map
	if(_entity_map.size() <= e)
	{
		//We add a buffer so we don't have to do this every time
		_entity_map.resize(e+MAPBUFFER, NOVAL);
	}

	//Set our Entity's component index
	_entity_map[e] = idx;
}

void LookupComponentManager::getMaxComponentIndex(Entity& e, int& idx)
{
	//Start with nothing
	e = NULL_ENTITY;
	idx = NOVAL;

	//Look through our Entity map...
	for(unsigned int i = 0; i < _entity_map.size(); i++)
	{
		//...for any index larger than what we already have...
		if(_entity_map[i] > idx)
		{
			//...and update our values if we find one
			idx = _entity_map[i];
			e = i;
		}
	}
}


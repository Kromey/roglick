// See header file for why this is here
#ifdef TLOOKUPCOMPONENTMANAGER_H_
#include "entity/components/TLookupComponentManager.h"

#define MAPBUFFER 5
#define NOVAL -1

template <typename T>
bool TLookupComponentManager<T>::entityHasComponent(Entity e)
{
	if(NULL_ENTITY == e || e >= _entity_map.size() || NOVAL == _entity_map[e])
	{
		return false;
	} else {
		return true;
	}
}

template <typename T>
void TLookupComponentManager<T>::addComponent(Entity e)
{
	setComponent(e, getNullComponent());
}

template <typename T>
void TLookupComponentManager<T>::removeComponent(Entity e)
{
	int idx = getComponentIndex(e);

	//Set our map to reflect that this Entity no longer has a component
	setComponentIndex(e, NOVAL);

	//Find the largest index in our entity_map
	int max_idx;
	Entity max_e;
	getMaxComponentIndex(max_e, max_idx);

	if(max_idx != idx)
	{
		//Fill the new gap with our current last component
		_components[idx] = _components[max_idx];
		setComponentIndex(max_e, idx);

		//Now shrink our vector to fit our new size
		_components.resize(_components.size() - 1);
	}
}

template <typename T>
T TLookupComponentManager<T>::getComponent(Entity e)
{
	if(entityHasComponent(e))
	{
		//Look up where the Entity's component is kept...
		int idx = getComponentIndex(e);
		//...and fetch it
		return _components[idx];
	} else {
		//Entity has no component
		return getNullComponent();
	}
}

template <typename T>
void TLookupComponentManager<T>::setComponent(Entity e, T comp)
{
	if(entityHasComponent(e))
	{
		int idx = getComponentIndex(e);
		_components[idx] = comp;
	} else {
		//Brand spankin' new component
		//Add this to our vector of componets
		_components.push_back(comp);

		//Make sure we have room in our Entity map
		setComponentIndex(e, _components.size()-1);
	}
}

template <typename T>
int TLookupComponentManager<T>::getComponentIndex(Entity e)
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

template <typename T>
void TLookupComponentManager<T>::setComponentIndex(Entity e, int idx)
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

template <typename T>
void TLookupComponentManager<T>::getMaxComponentIndex(Entity& e, int& idx)
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

#endif

// See header file for why this is here
#ifdef MULTILOOKUPCOMPONENTMANAGER_H_

#include <utility>

#include "entity/managers/base/MultiLookupComponentManager.h"

template<typename Ti, typename T>
std::map<Ti,T> MultiLookupComponentManager<Ti,T>::getNullComponent()
{
	//Just an empty map
	std::map<Ti,T> empty;
	return empty;
}

template<typename Ti, typename T>
T MultiLookupComponentManager<Ti,T>::getComponent(Entity e, Ti type)
{
	//Get our current sub-components
	std::map<Ti, T> comp_map = getComponent(e);
	//Look for the one we're after
	typename std::map<Ti, T>::iterator comp_it = comp_map.find(type);

	if(comp_map.end() == comp_it)
	{
		//Not found, return our NULL-equivalent
		return getNullSubComponent();
	} else {
		//Return the specified sub-component
		return comp_it->second; //first is key, second is value
	}
}

template<typename Ti, typename T>
std::map<Ti,T> MultiLookupComponentManager<Ti,T>::getComponent(Entity e)
{
	//All we need to do really is call the parent class's method -- simple!
	return LookupComponentManager< std::map<Ti,T> >::getComponent(e);
}

template<typename Ti, typename T>
void MultiLookupComponentManager<Ti,T>::setComponent(Entity e, Ti type, T value)
{
	//Get our current components
	std::map<Ti, T> comp_map = getComponent(e);

	//Update the individual one to the specified value
	comp_map[type] = value;

	//Now update the whole thing
	LookupComponentManager< std::map<Ti,T> >::setComponent(e, comp_map);
}

template<typename Ti, typename T>
void MultiLookupComponentManager<Ti,T>::setComponent(Entity e, std::map<Ti,T> comp)
{
	//All we need to do really is call the parent class's method -- simple!
	LookupComponentManager< std::map<Ti,T> >::setComponent(e, comp);
}

#endif

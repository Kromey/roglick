// See header file for why this is here
#ifdef MULTILOOKUPCOMPONENTMANAGER_H_

#include <utility>

#include "entity/managers/base/MultiLookupComponentManager.h"

template<typename Ti, typename T>
T MultiLookupComponentManager<Ti,T>::getComponent(Entity e, Ti type)
{
	std::map<Ti, T> comp_map = getComponent(e);
	std::map<Ti, T>::iterator comp_it = comp_map.find(Ti);

	if(comp_map.end() == comp_it)
	{
		return getNullComponent();
	} else {
		return comp_it->second();
	}
}

void MultiLookupComponentManager<Ti,T>::setComponent(Entity e, Ti type, T value)
{
	std::map<Ti, T> comp_map = getComponent(e);

	comp_map.insert(std::pair<Ti,T>(type, value));

	setComponent(e, comp_map);
}

#endif

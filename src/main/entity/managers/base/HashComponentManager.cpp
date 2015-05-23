// See header file for why this is here
#ifdef LOOKUPCOMPONENTMANAGER_H_
#include "entity/managers/base/LookupComponentManager.h"

#include <utility>

#include "entity/managers/base/HashComponentManager.h"

template <typename T>
bool HashComponentManager::entityHasComponent(Entity e)
{
	return _components.end() != _components.find(e);
}

template <typename T>
void HashComponentManager::addComponent(Entity e)
{
	setTarget(e, getNullComponent());
}

template <typename T>
void HashComponentManager::removeComponent(Entity e)
{
	_components.erase(e);
}

template <typename T>
TargetComponent HashComponentManager::getTarget(Entity e)
{
	//.find() gets an iterator with one clunky signature!
	std::map<Entity, T>::iterator it = _components.find(e);

	if(_components.end() == it)
	{
		return getNullComponent(); //no target
	} else {
		return it->second; //first is the key; second is the value
	}
}

template <typename T>
void HashComponentManager::setComponent(Entity e, T comp)
{
	_components.insert( std::pair<Entity, T>(e, comp) );
}

#endif

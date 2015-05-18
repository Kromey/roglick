#include <utility>

#include "entity/components/TargetManager.h"

const TargetComponent TargetManager::NULL_TARGET = { NULL_ENTITY };

TargetManager::TargetManager()
{
}

bool TargetManager::entityHasComponent(Entity e)
{
	return _targets.end() != _targets.find(e);
}

void TargetManager::addComponent(Entity e)
{
	setTarget(e, NULL_TARGET);
}

void TargetManager::removeComponent(Entity e)
{
	_targets.erase(e);
}

TargetComponent TargetManager::getTarget(Entity e)
{
	//.find() gets an iterator with one clunky signature!
	std::map<Entity, TargetComponent>::iterator it = _targets.find(e);

	if(_targets.end() == it)
	{
		return NULL_TARGET; //no target
	} else {
		return it->second; //first is the key; second is the value
	}
}

void TargetManager::setTarget(Entity e, TargetComponent target)
{
	_targets.insert( std::pair<Entity, TargetComponent>(e, target) );
}

void TargetManager::setTarget(Entity e, Entity target)
{
	TargetComponent tc = { target };
	setTarget(e, tc);
}


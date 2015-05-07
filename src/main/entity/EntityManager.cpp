#include <cstddef>

#include "entity/EntityManager.h"

EntityManager::EntityManager()
{
	//Our first Entity is always the 0th one.
	_next_entity = 0;
}

Entity EntityManager::createEntity()
{
	//Get the next Entity
	Entity e = _next_entity;
	//Now increment the next next Entity
	++_next_entity;

	if(NULL_ENTITY == e)
	{
		//Oops! We can't use NULL_ENTITY!
		return createEntity(); //Let's simply try again
	} else {
		//Add this Entity to the list of Entities
		_entities.insert(e);

		//Finally return the created Entity
		return e;
	}
}

bool EntityManager::isEntityAlive(Entity e)
{
	//We're dealing with a set, which returns set::end if it doesn't find the
	//value we're looking for.
	return _entities.find(e) != _entities.end();
}

void EntityManager::destroyEntity(Entity e)
{
	//Removing an Entity from our set destroys it.
	_entities.erase(e);
}

EntityList EntityManager::getEntities()
{
	//This is safe because, since we're returning by value, a copy is made and
	//returned rather than our actual internal list.
	return _entities;
}

void EntityManager::addComponentManager(ComponentManager* cm)
{
	_component_managers.push_back(cm);
}

ComponentManager* EntityManager::getComponentManager(component_t type)
{
	//Iterate through our list of managers, find the one we want
	for(std::vector<ComponentManager*>::iterator it = _component_managers.begin();
		it != _component_managers.end(); ++it)
	{
		//Remember that dereferencing the iterator gives us a pointer still
		if(type == (*it)->getComponentType())
		{
			//We found it, so just return it straight away.
			return *it;
		}
	}

	//We found no such manager, sad panda is sad!
	return NULL;
}


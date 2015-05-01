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

	//Add this Entity to the list of Entities
	_entities.insert(e);

	//Finally return the created Entity
	return e;
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

void EntityManager::addComponentManager(ComponentManager* cm)
{
	_component_managers.push_back(cm);
}

ComponentManager* EntityManager::getComponentManager(int idx)
{
	return _component_managers[idx];
}


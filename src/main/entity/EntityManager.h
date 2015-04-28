#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <set>

#include "entity/Entity.h"

/**
 * Class responsible for managing Entity state.
 *
 * The EntityManager creates, tests, and destroys @link Entities Entity @endlink
 * as needed, maintaining knowledge of which ones are and are not still "alive";
 * this is important because we only maintain weak references between an Entity
 * and its Component%s, therefore at any given moment there could be multiple
 * references out there held to a long-dead Entity.
 */
class EntityManager
{
	public:
		/**
		 * Constructor initializes the manager by establishing the first Entity
		 * to be created.
		 */
		EntityManager();

		/**
		 * Create a new Entity.
		 *
		 * @return The new Entity.
		 */
		Entity createEntity();

		/**
		 * Test if the given Entity is still a valid one in the system.
		 *
		 * @param e The Entity to test.
		 *
		 * @return True if valid, false otherwise.
		 */
		bool isEntityAlive(Entity e);

		/**
		 * Destroy the given Entity.
		 *
		 * @param e The Entity to destroy.
		 */
		void destroyEntity(Entity e);

	private:
		/**
		 * Maintains our list of valid Entities.
		 */
		std::set<Entity> _entities;

		/**
		 * The next Entity we will create.
		 */
		Entity _next_entity;
};

#endif

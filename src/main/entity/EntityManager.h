#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <set>
#include <vector>

#include "entity/Entity.h"
#include "entity/components/ComponentManager.h"

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

		/**
		 * Add a ComponentManager object to this manager, allowing them to add
		 * their relevant Components to any Entity in this manager.
		 *
		 * @param cm Pointer to the ComponentManager subclass to add.
		 */
		void addComponentManager(ComponentManager* cm);

		/**
		 * Retrieve the ComponentManager referenced by the given index.
		 *
		 * @param idx The index of the ComponentManager from addComponentManager
		 *
		 * @return Pointer to the referenced ComponentManager
		 */
		ComponentManager* getComponentManager(int idx);

	private:
		/**
		 * Maintains our list of valid Entities.
		 */
		std::set<Entity> _entities;

		/**
		 * The next Entity we will create.
		 */
		Entity _next_entity;

		std::vector<ComponentManager*> _component_managers;
};

#endif

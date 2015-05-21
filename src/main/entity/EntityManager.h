#ifndef ENTITYMANAGER_H_
#define ENTITYMANAGER_H_

#include <set>
#include <vector>

#include "entity/Entity.h"
#include "entity/managers/base/ComponentManager.h"

/**
 * Class responsible for managing Entity state.
 *
 * The EntityManager creates, tests, and destroys @link Entity Entities @endlink
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
		 * Retrieve a list of all living Entities.
		 *
		 * @return List of Entities
		 */
		EntityList getEntities();

		/**
		 * Add a ComponentManager object to this manager, allowing them to add
		 * their relevant Components to any Entity in this manager.
		 *
		 * @param cm Pointer to the ComponentManager subclass to add.
		 */
		void addComponentManager(ComponentManager* cm);

		/**
		 * Retrieve the ComponentManager for the given component.
		 *
		 * @param type The type of Component to get the manager of.
		 *
		 * @return Pointer to the referenced ComponentManager
		 */
		ComponentManager* getComponentManager(component_t type);

	private:
		/**
		 * Go through our list of ComponentManager%s and make sure this Entity
		 * has all components removed. This is most useful when destroying an
		 * Entity, to ensure that its identifier doesn't later get attached to
		 * stale data.
		 *
		 * @param e The Entity to remove components from
		 */
		void purgeEntityComponents(Entity e);

		/**
		 * Maintains our list of valid Entities.
		 */
		EntityList _entities;

		/**
		 * The next Entity we will create.
		 */
		Entity _next_entity;

		std::vector<ComponentManager*> _component_managers;
};

#endif

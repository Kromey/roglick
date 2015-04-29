#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "entity/Entity.h"
#include "entity/components/Component.h"

/**
 * Base class for all Component Managers.
 */
class ComponentManager
{
	public:
		/**
		 * Check if the given Entity has this manager's Component.
		 *
		 * @param e The Entity to test for.
		 *
		 * @return True if the Entity has this Component.
		 */
		virtual bool entityHasComponent(Entity e) = 0;

		/**
		 * Add the Component to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 * @param c The Component to add.
		 */
		virtual void addComponent(Entity e, Component* c) = 0;

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e) = 0;

		/**
		 * Retrieve the Entity's Component.
		 *
		 * This method will return NULL if the Entity does not have
		 * this Component.
		 *
		 * @param e The Entity to get the Component for.
		 *
		 * @return The Entity's Component.
		 */
		virtual Component* getComponent(Entity e) = 0;
	
	protected:
		/**
		 * This class must be inherited, it cannot be instantiated directly.
		 *
		 * NB: We actually gain this from having pure virtual methods already,
		 * but it can't hurt to have an extra layer e.g. in case for any reason
		 * we start to implement default versions of the above.
		 */
		ComponentManager() {};
};

#endif

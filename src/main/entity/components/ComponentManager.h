#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "entity/Entity.h"

/**
 * Enumeration for each of our types of components
 */
enum component_t {
	Position,
	Render
};

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
		 * Add the Component (with default values) to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 */
		virtual void addComponent(Entity e) = 0;

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e) = 0;

		/**
		 * Gets the type of component that this ComponentManager subclass
		 * manages.
		 *
		 * @return One of the component_t enumerations.
		 */
		virtual component_t getComponentType() = 0;

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

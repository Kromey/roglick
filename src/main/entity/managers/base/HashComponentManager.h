#ifndef HASHCOMPONENTMANAGER_H_
#define HASHCOMPONENTMANAGER_H_

#include <map>

#include "entity/Entity.h"
#include "entity/managers/base/ComponentManager.h"

/**
 * This class implements a very simple, heap-like storage for components that
 * the large majority of Entities do not have.
 *
 * This class is optimized for storing small numbers of components in as little
 * space as possible, with as little storage overhead as possible; a side
 * effect of this is that lookups are relatively expensive, especially compared
 * to LookupComponentManager.
 */
template <typename T>
class HashComponentManager : public ComponentManager
{
	public:
		/**
		 * Abstract method to get the NULL-equivalent value for this component.
		 *
		 * @return The NULL-equivalent value for the component.
		 */
		virtual T getNullComponent() = 0;

		/**
		 * Test if the given Entity has this component or not.
		 *
		 * @param e
		 *
		 * @return True if the Entity e has it
		 */
		virtual bool entityHasComponent(Entity e);

		/**
		 * Add the Component to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 */
		virtual void addComponent(Entity e);

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e);

		/**
		 * Retrieve the component of the given Entity. Returns the appropriate
		 * NULL-equivalent component it the Entity does not have one.
		 *
		 * @param e Entity to get the position of.
		 *
		 * @return The Entity's component
		 */
		T getComponent(Entity e);
		/**
		 * Set the component for the given Entity.
		 *
		 * @param e The Entity
		 * @param comp Component for this Entity
		 */
		virtual void setComponent(Entity e, T comp);

	protected:
		/**
		 * Prevent this class ever being directly instantiated.
		 */
		HashComponentManager() {};
		/**
		 * Simple key-value pairing of our Entities and components.
		 */
		std::map<Entity, T> _components;
};

/**
 * We have to include our .cpp file here because any time a new "form" of a
 * template is used, the implementation of the methods has to also be available
 * so that the compiler can build the proper symbols for the linker.
 *
 * @todo Can we figure out a cleaner way to include the template implementation?
 */
#include "entity/managers/base/HashComponentManager.cpp"

#endif

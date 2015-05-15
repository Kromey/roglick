#ifndef TLOOKUPCOMPONENTMANAGER_H_
#define TLOOKUPCOMPONENTMANAGER_H_

#include <vector>

#include "entity/components/ComponentManager.h"

/**
 * Abstract class that implements the basic "lookup table" pattern for Entity
 * ComponentManager subclasses. Extend this class if you are implementing a
 * ComponentManager for which many Entities would have the component.
 *
 * This class is a template, but it is only intended to be implemented with
 * components.
 */
template <typename T>
class TLookupComponentManager : public ComponentManager
{
	public:
		virtual T getNullComponent() = 0;

		/**
		 * Check if the given Entity has this manager's Component.
		 *
		 * @param e The Entity to test for.
		 *
		 * @return True if the Entity has this Component.
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
		 * Retrieve the component of the given Entity. Returns the component's
		 * NULL-equivalent value if the Entity does not have one.
		 *
		 * @param e Entity to get the component of.
		 *
		 * @return The Entity's component
		 */
		virtual T getComponent(Entity e);
		/**
		 * Set the component for the given Entity.
		 *
		 * @param e The Entity
		 * @param comp Component for this Entity
		 */
		virtual void setComponent(Entity e, T comp);

	protected:
		/**
		 * This class must be inherited, it cannot be instantiated directly.
		 */
		TLookupComponentManager() {};

		/**
		 * Returns the component index for the given Entity.
		 *
		 * @param e
		 *
		 * @return The index
		 */
		virtual int getComponentIndex(Entity e);
		/**
		 * Apply the specified index for the given Entity.
		 *
		 * This method will ensure that there is enough space for the map,
		 * buffering so that new components don't always require re-allocating
		 * space in the map.
		 *
		 * @param e
		 * @param idx
		 */
		virtual void setComponentIndex(Entity e, int idx);

		/**
		 * Search our map for the largest current index.
		 *
		 * This method is useful when removing a component so that "gaps" in
		 * the component list can be filled.
		 *
		 * @param[out] e Entity owning this index
		 * @param[out] idx The largest index in the map
		 */
		virtual void getMaxComponentIndex(Entity& e, int& idx);

		/**
		 * The lookup table to find a component for any given Entity.
		 *
		 * To make lookups quick, the Entity is itself the index into this
		 * vector; the value is the index for the component. While this may
		 * result in some gaps in the map (filled with NOVAL as the value),
		 * ultimately the tradeoff in a little more memory in exchange for
		 * improved speed should be worth it for components that are
		 * accessed frequently or for components that all or nearly Entities
		 * have.
		 */
		std::vector<int> _entity_map;

		std::vector<T> _components;
};

/**
 * We have to include our .cpp file here because any time a new "form" of a
 * template is used, the implementation of the methods has to also be available
 * so that the compiler can build the proper symbols for the linker.
 *
 * @todo Can we figure out a cleaner way to include the template implementation?
 */
#include "entity/components/TLookupComponentManager.cpp"

#endif

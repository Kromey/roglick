#ifndef LOOKUPCOMPONENTMANAGER_H_
#define LOOKUPCOMPONENTMANAGER_H_

#include <vector>

#include "entity/components/ComponentManager.h"

/**
 * Abstract class that implements the basic "lookup table" pattern for Entity
 * ComponentManager subclasses. Extend this class if you are implementing a
 * ComponentManager for which many Entities would have the component.
 */
class LookupComponentManager : public ComponentManager
{
	public:
		/**
		 * Check if the given Entity has this manager's Component.
		 *
		 * @param e The Entity to test for.
		 *
		 * @return True if the Entity has this Component.
		 */
		virtual bool entityHasComponent(Entity e);

	protected:
		/**
		 * This class must be inherited, it cannot be instantiated directly.
		 */
		LookupComponentManager() {};

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
};

#endif

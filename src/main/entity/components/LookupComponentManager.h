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
		LookupComponentManager();

		virtual int addComponentIndex(Entity e);
		virtual int getComponentIndex(Entity e);
		virtual void setComponentIndex(Entity e, int idx);

		virtual void getMaxComponentIndex(Entity& e, int& idx);

		std::vector<int> _entity_map;

};

#endif

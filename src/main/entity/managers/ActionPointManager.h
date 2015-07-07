#ifndef ACTIONPOINTMANAGER_H_
#define ACTIONPOINTMANAGER_H_

#include "entity/Entity.h"
#include "entity/managers/base/LookupComponentManager.h"
#include "entity/components/ActionPointComponent.h"

/**
 */
class ActionPointManager : public LookupComponentManager<ActionPointComponent>
{
	public:
		/**
		 * Default and NULL-equivalent ActionPointComponent value.
		 */
		static const ActionPointComponent NULL_ACTIONPOINT;

		/**
		 * Return a NULL_ACTIONPOINT ActionPointComponent
		 *
		 * @return NULL_ACTIONPOINT
		 */
		virtual ActionPointComponent getNullComponent()
			{ return NULL_ACTIONPOINT; };

		/**
		 * Constructor.
		 */
		ActionPointManager();

		/**
		 * ActionPointManager is the ComponentManager sub-class for ActionPoints.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return ActionPoints; };

};

#endif

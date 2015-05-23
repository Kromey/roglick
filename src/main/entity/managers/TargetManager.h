#ifndef TARGETMANAGER_H_
#define TARGETMANAGER_H_

#include <map>

#include "entity/Entity.h"
#include "entity/managers/base/HashComponentManager.h"
#include "entity/components/TargetComponent.h"

/**
 * TargetManager is the ComponentManager for Target components.
 *
 * A Target is, quite simply, the Entity being attacked by this one.
 */
class TargetManager : public HashComponentManager<TargetComponent>
{
	public:
		/**
		 * Default and NULL-equivalent TargetComponent value.
		 */
		static const TargetComponent NULL_TARGET;

		/**
		 * Return a NULL_TARGET TargetComponent
		 *
		 * @return NULL_TARGET
		 */
		virtual TargetComponent getNullComponent() { return NULL_TARGET; };

		/**
		 * Constructor
		 */
		TargetManager();

		/**
		 * TargetManager is the ComponentManager sub-class for Target.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Target; };
};

#endif

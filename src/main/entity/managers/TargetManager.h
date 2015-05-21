#ifndef TARGETMANAGER_H_
#define TARGETMANAGER_H_

#include <map>

#include "entity/Entity.h"
#include "entity/managers/base/ComponentManager.h"
#include "entity/components/TargetComponent.h"

/**
 * TargetManager is the ComponentManager for Target components.
 *
 * A Target is, quite simply, the Entity being attacked by this one.
 */
class TargetManager : public ComponentManager
{
	public:
		/**
		 * Default and NULL-equivalent TargetComponent value.
		 */
		static const TargetComponent NULL_TARGET;

		/**
		 * Constructor
		 */
		TargetManager();

		/**
		 * Test if the given Entity has a TargetComponent or not.
		 *
		 * @param e
		 *
		 * @return True if the Entity e has a TargetComponent
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
		 * TargetManager is the ComponentManager sub-class for Target.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Target; };

		/**
		 * Retrieve the target of the given Entity. Returns NULL_SPRITE if
		 * the Entity does not have a TargetComponent.
		 *
		 * @param e Entity to get the position of.
		 *
		 * @return The Entity's TargetComponent
		 */
		TargetComponent getTarget(Entity e);
		/**
		 * Set the TargetComponent for the given Entity.
		 *
		 * @param e The Entity
		 * @param target TargetComponent for this Entity
		 */
		void setTarget(Entity e, TargetComponent target);
		/**
		 * Set the TargetComponent for the Entity e to be the Entity target.
		 *
		 * @param e The Entity
		 * @param target The Entity targeted by e
		 */
		void setTarget(Entity e, Entity target);

	private:
		std::map<Entity, TargetComponent> _targets;
};

#endif

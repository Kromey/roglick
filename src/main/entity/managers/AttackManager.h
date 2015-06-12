#ifndef ATTACKMANAGER_H_
#define ATTACKMANAGER_H_

#include <map>

#include "entity/Entity.h"
#include "entity/managers/base/HashComponentManager.h"
#include "entity/components/AttackComponent.h"

/**
 * AttackManager is the ComponentManager for AttackComponent%s.
 *
 * An Attack is exactly what it says on the tin.
 */
class AttackManager : public HashComponentManager<AttackComponent>
{
	public:
		/**
		 * Default and NULL-equivalent AttackComponent value.
		 */
		static const AttackComponent NULL_ATTACK;

		/**
		 * Return a NULL_ATTACK AttackComponent
		 *
		 * @return NULL_ATTACK
		 */
		virtual AttackComponent getNullComponent() { return NULL_ATTACK; };

		/**
		 * Constructor
		 */
		AttackManager();

		/**
		 * AttackManager is the ComponentManager sub-class for Attack.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Attack; };
};

#endif

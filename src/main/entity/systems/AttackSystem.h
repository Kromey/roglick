#ifndef ATTACKSYSTEM_H_
#define ATTACKSYSTEM_H_

#include "entity/systems/System.h"

/**
 * System responsible for handling @link Entity Entities @endlink attacking
 * other Entities.
 */
class AttackSystem : public System
{
	public:
		/**
		 * Default constructor.
		 */
		AttackSystem();

		/**
		 * Process all @link Entity Entities @endlink and resolve any that are
		 * attacking.
		 *
		 * @param em Reference to the EntityManager
		 */
		virtual void execute(EntityManager& em);

	private:
};

#endif

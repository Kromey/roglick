#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "entity/EntityManager.h"

/**
 * System%s are the workhorses of the ECS architecture.
 *
 * A System takes care of the actual execution of game logic, each one being
 * responsible for one concrete "slice" of the game's rules and mechanics.
 */
class System
{
	public:
		/**
		 * This is the method that is called on each System to make it do its
		 * thing -- whatever that "thing" is. It takes as a single argument a
		 * reference to the EntityManager responsible for the @link Entity
		 * Entities @endlink that it should be run on.
		 *
		 * @param em Reference to the EntityManager
		 */
		virtual void execute(EntityManager& em) = 0;

	protected:
		/**
		 * Protected because this class cannot be instantiated directly.
		 */
		System() {};
};

#endif

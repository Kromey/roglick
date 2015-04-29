#ifndef COMPONENT_H_
#define COMPONENT_H_

/**
 * Abstract base class for all Components to provide type safety for methods
 * that act on them.
 */
class Component
{
	protected:
		/**
		 * Cannot be directly instantiated, must be used as a base class.
		 */
		Component();
}

#endif

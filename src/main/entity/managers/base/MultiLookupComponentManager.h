#ifndef MULTILOOKUPCOMPONENTMANAGER_H_
#define MULTILOOKUPCOMPONENTMANAGER_H_

#include <map>

#include "entity/managers/base/LookupComponentManager.h"

/**
 * 
 *
 * @tparam Ti The type or identifier for each sub-component
 * @tparam T  The sub-component
 */
template <typename Ti, typename T>
class MultiLookupComponentManager :
	public LookupComponentManager< std::map<Ti,T> >
{
	public:
		/**
		 * Returns an empty list of sub-components.
		 *
		 * @return An empty list
		 */
		virtual std::map<Ti,T> getNullComponent();

		/**
		 * Return a NULL-equivalent sub-component.
		 *
		 * @return The NULL-equivalent for this type of component
		 */
		virtual T getNullSubComponent() = 0;

		/**
		 * Get the individual sub-component identified by type.
		 *
		 * @param e The Entity
		 * @param type The identifier for the sub-component we want
		 *
		 * @return The referenced sub-component
		 */
		virtual T getComponent(Entity e, Ti type);
		virtual std::map<Ti,T> getComponent(Entity e);

		/**
		 * Set the individual sub-component identified by type.
		 *
		 * @param e The Entity
		 * @param type Identifier for the sub-component to set
		 * @param value Value to set the sub-component to
		 */
		virtual void setComponent(Entity e, Ti type, T value);
};

/**
 * We have to include our .cpp file here because any time a new "form" of a
 * template is used, the implementation of the methods has to also be available
 * so that the compiler can build the proper symbols for the linker.
 *
 * @todo Can we figure out a cleaner way to include the template implementation?
 */
#include "entity/managers/base/MultiLookupComponentManager.cpp"

#endif

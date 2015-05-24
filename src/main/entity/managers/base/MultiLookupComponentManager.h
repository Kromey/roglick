#ifndef MULTILOOKUPCOMPONENTMANAGER_H_
#define MULTILOOKUPCOMPONENTMANAGER_H_

#include <map>

#include "entity/managers/base/LookupComponentManager.h"

template <typename Ti, typename T>
class MultiLookupComponentManager : public LookupComponentManager<std::map<Ti,T>>
{
	virtual T getComponent(Entity e, Ti type);

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

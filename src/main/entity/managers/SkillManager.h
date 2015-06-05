#ifndef SKILLMANAGER_H_
#define SKILLMANAGER_H_

#include "entity/Entity.h"
#include "entity/managers/base/MultiLookupComponentManager.h"
#include "entity/components/SkillComponent.h"

/**
 * AttributeManager is the ComponentManager for Attribute components.
 *
 * Attributes define the basic capabilities of an Entity.
 */
class AttributeManager :
	public MultiLookupComponentManager<skill_t, SkillComponent>
{
};

#endif

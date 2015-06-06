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
class SkillManager :
	public MultiLookupComponentManager<skill_t, SkillComponent>
{
	public:
		/**
		 * Default and NULL-equivalent SkillComponent value.
		 */
		static const SkillComponent NULL_SKILL;

		/**
		 * Return a NULL_SKILL SkillComponent
		 *
		 * @return NULL_SKILL
		 */
		virtual SkillComponent getNullSubComponent() { return NULL_SKILL; };

		/**
		 * Constructor.
		 */
		SkillManager();

		/**
		 * SkillManager is the ComponentManager sub-class for Skill.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Skill; };

};

#endif

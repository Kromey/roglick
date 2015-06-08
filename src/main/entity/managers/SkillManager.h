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

		virtual int getSkillLevel(Entity e, skill_t skill);

		/**
		 * Retrieves the parent skill ID for the given skill.
		 *
		 * This method will return the same skill ID if it has no parent.
		 *
		 * @param skill The skill ID to get the parent of
		 *
		 * @return The ID of the parent skill, or skill if no parent.
		 */
		virtual skill_t getParentSkill(skill_t skill);
};

#endif

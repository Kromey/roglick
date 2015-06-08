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

		/**
		 * Add XP to the specified skill of the given Entity.
		 *
		 * This method also takes care of adding the appropriate amount of XP
		 * to the skill's parent skill(s), and will even increment the skill's
		 * level when appropriate.
		 *
		 * @param e The Entity
		 * @param skill The Skill
		 * @param xp The amount of XP to add
		 */
		void addXP(Entity e, skill_t skill, int xp);

		/**
		 * Add default XP to the specified skill.
		 * @see addXP(Entity, skill_t, int)
		 *
		 * @param e The Entity
		 * @param skill The Skill
		 */
		void addXP(Entity e, skill_t skill);

		/**
		 * Calculate the level of an Entity's skill.
		 *
		 * This calculation has to take into account not only the skill's
		 * ranks, but also those of the parent skill(s), as well as the
		 * controlling attribute's damage level.
		 *
		 * @param e The Entity
		 * @param skill The Skill
		 *
		 * @return The level of the skill
		 */
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

	private:
		/**
		 * Add a raw amount to the Entity's XP sum for the given skill.
		 *
		 * @param e The Entity
		 * @param skill The Skill
		 * @param raw_xp The raw (scaled) XP
		 */
		void addRawXP(Entity e, skill_t skill, int raw_xp);
};

#endif

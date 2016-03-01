#ifndef SKILLMANAGER_H_
#define SKILLMANAGER_H_

#include "entity/Entity.h"
#include "entity/managers/base/MultiLookupComponentManager.h"
#include "entity/managers/AttributeManager.h"
#include "entity/components/SkillComponent.h"
#include "core/Dice.h"

/**
 * Data structure to represent the results of a skill check
 */
typedef struct
{
	int roll; ///< The actual dice roll
	int dos; ///< The check's Degree of Success (if successful)
	bool successful; ///< True if the check was passed
	bool is_critical; ///< True if the check was a Critical Success
} SkillCheckResult;

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
		 * Provide this manager with a pointer to the AttributeManager to allow
		 * it to look up attributes and, from there, calculate the penalties to
		 * skills as a result of attribute damage.
		 *
		 * @param am Pointer to the AttributeManager object
		 */
		void setAttributeManager(AttributeManager* am) { _attribute_manager = am; };

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
		 * This method will return None if it has no parent.
		 *
		 * @param skill The skill ID to get the parent of
		 *
		 * @return The ID of the parent skill, or None if no parent.
		 */
		virtual skill_t getParentSkill(skill_t skill);
		/**
		 * Retrieves the given skill's related attribute.
		 *
		 * @param skill The skill to get the attribute of
		 *
		 * @return The skill's related attribute
		 */
		virtual attrtype_t getSkillAttribute(skill_t skill);

		/**
		 * Perform a skill check with no modifier.
		 *
		 * @see check(Entity, skill_t, int)
		 *
		 * @param e The Entity
		 * @param skill The skill to test
		 *
		 * @return A SkillCheckResult object containing the check's results
		 */
		SkillCheckResult check(Entity e, skill_t skill);
		/**
		 * Perform a skill check.
		 *
		 * The skill is first modified by the value of modifier (which may be
		 * negative (i.e. a penalty)), and then the skill is tested with a 3d6
		 * roll; if the sum is less than or equal to the modified skill level,
		 * then the check is successful and this method will return true.
		 *
		 * @sideeffect The return value of getLastDoS will change after any call
		 * to this method.
		 *
		 * @param e The Entity
		 * @param skill The skill to test
		 * @param modifier Modifier to apply to the skill level
		 *
		 * @return A SkillCheckResult object containing the check's results
		 */
		SkillCheckResult check(Entity e, skill_t skill, int modifier);

		/**
		 * Retrieve the last DoS (Degree of Success) of a skill check.
		 *
		 * This method always returns the results of the *last* call to
		 * check(Entity, skill_t, int).
		 *
		 * @return The last skill check's DoS
		 */
		int getLastDoS();

	private:
		/**
		 * Add a raw amount to the Entity's XP sum for the given skill.
		 *
		 * @param e The Entity
		 * @param skill The Skill
		 * @param raw_xp The raw (scaled) XP
		 */
		void addRawXP(Entity e, skill_t skill, int raw_xp);

		/**
		 * Retrieves and calculates the skill's level, taking into account
		 * parent skills but not attribute damage.
		 *
		 * @param e The Entity
		 * @param skill The skill
		 *
		 * @return The skill's level
		 */
		int getBaseSkillLevel(Entity e, skill_t skill);

		/**
		 * Calculates and returns the penalty to a skill's level as a result of
		 * attribute damage.
		 *
		 * @param e The Entity
		 * @param skill The skill
		 *
		 * @return The penalty to apply to the skill's level
		 */
		int getAttributePenalty(Entity e, skill_t skill);

		/**
		 * Dice object for tests against skills.
		 */
		Dice _dice;

		/**
		 * Store the last DoS (Degree of Success) of a skill check.
		 */
		int _last_dos;

		AttributeManager* _attribute_manager;
};

#endif

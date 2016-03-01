#include <cstddef>

#include "entity/managers/SkillManager.h"

#define LEVELUP 250

const SkillComponent SkillManager::NULL_SKILL = { 0, 0 };

SkillManager::SkillManager() : _dice(3, 6) //Initialize our 3d6 Dice object
{
	_attribute_manager = NULL;
}

void SkillManager::addXP(Entity e, skill_t skill, int xp)
{
	//If we have a parent skill...
	skill_t parent = getParentSkill(skill);
	if(None != parent)
	{
		//...then we have a parent skill, and add half our XP to it
		addXP(e, parent, xp/2);
	}

	SkillComponent the_skill = getComponent(e, skill);

	the_skill.xp += xp;

	//The threshold is based on the next number of ranks
	int threshold = (the_skill.ranks + 1) * LEVELUP;
	if(the_skill.xp >= threshold)
	{
		the_skill.ranks += 1;
		the_skill.xp -= threshold;
	}

	setComponent(e, skill, the_skill);
}

int SkillManager::getSkillLevel(Entity e, skill_t skill)
{
	int level = getBaseSkillLevel(e, skill);
	int penalty = getAttributePenalty(e, skill);

	return level - penalty;
}

skill_t SkillManager::getParentSkill(skill_t skill)
{
	//We simply have a global constant map for this (for now...)
	return SkillTree.find(skill)->second.parent;
}

attrtype_t SkillManager::getSkillAttribute(skill_t skill)
{
	//We simply have a global constant map for this (for now...)
	return SkillTree.find(skill)->second.attribute;
}

SkillCheckResult SkillManager::check(Entity e, skill_t skill)
{
	return check(e, skill, 0); //Do a check with no modifier
}

SkillCheckResult SkillManager::check(Entity e, skill_t skill, int modifier)
{
	int skill_level = getSkillLevel(e, skill) + modifier;
	// A check is successful if a 3d6 roll is less than or equal to the level
	int roll = _dice.roll();
	///@todo Check for Critical Success
	SkillCheckResult result = {roll, skill_level-roll, roll<=skill_level, false};

	// Now calculate XP for the skill based on the result
	int xp;
	AttributeComponent attr = _attribute_manager->getComponent(e, getSkillAttribute(skill));
	if(result.successful)
	{
		// A successful check, gain full XP
		xp = calculateXP(skill_level, attr);
	} else {
		xp = calculateXPFailed(skill_level, attr);
	}
	addXP(e, skill, xp);

	return result;
}

int SkillManager::getLastDoS()
{
	return _last_dos;
}

int SkillManager::calculateXP(int skill_level, AttributeComponent attr)
{
	int diff = attr.cur - skill_level;
	if(diff < 1)
	{
		diff = 1;
	}

	Dice dice(diff, attr.cur);
	return dice.roll();
}

int SkillManager::calculateXPFailed(int skill_level, AttributeComponent attr)
{
	return calculateXP(skill_level, attr) / (1 + skill_level);
}

int SkillManager::getBaseSkillLevel(Entity e, skill_t skill)
{
	int parent_level = 0;

	//If getParentSkill doesn't give us our same skill back...
	if(getParentSkill(skill) != skill)
	{
		//...then we have a parent skill
		parent_level = getBaseSkillLevel(e, getParentSkill(skill));
	}

	int ranks = getComponent(e, skill).ranks;

	//Skill level is equal to ranks plus 1/2 parent skill's level
	///@todo Need to accomodate "default skill"
	return ranks + (parent_level / 2);
}

int SkillManager::getAttributePenalty(Entity e, skill_t skill)
{
	if(NULL != _attribute_manager)
	{
		attrtype_t attribute = getSkillAttribute(skill);

		AttributeComponent attr = _attribute_manager->getComponent(e, attribute);
		/**
		 * A Skill is penalized by 1 point for each *full* 20% increment
		 * that its associated Attribute has lost, e.g. an Attribute at 81% of
		 * its full value would incur no penalty for its associated Skills, but
		 * at 80% its Skills suffer a -1 penalty.
		 *
		 * To avoid the imprecision of floating-point arithmetic, however, we do
		 * our calculations with integers, which has the happy side effect of
		 * also eliminating the need for any round() or floor() calls:
		 *
		 * \f{eqnarray*}{
		 *  AttrDmg &=& AttrMax - AttrCur \\
		 *  AttrRatio &=& \frac{AttrDmg \times 100}{AttrMax} \\
		 *  Penalty &=& \frac{AttrRatio}{20} \\
		 *  Penalty &=& \frac{\frac{AttrDmg \times 100}{AttrMax}}{20} \\
		 *  Penalty &=& \frac{AttrDmg \times 100}{20} \times \frac{1}{AttrMax} \\
		 *  Penalty &=& (AttrDmg \times 5) \times \frac{1}{AttrMax} \\
		 *  Penalty &=& (AttrMax - AttrCur) \times \frac{5}{AttrMax}
		 * \f}
		 */
		return (attr.max - attr.cur) * 5 / attr.max;
	}

	return 0;
}


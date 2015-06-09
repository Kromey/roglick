#include <cstddef>
#include <iostream>

#include "entity/managers/SkillManager.h"

#define XPSCALE 1000
#define LEVELUP 10

const SkillComponent SkillManager::NULL_SKILL = { 0, 0 };

SkillManager::SkillManager() : _dice(3, 6) //Initialize our 3d6 Dice object
{
	_attribute_manager = NULL;
}

void SkillManager::addXP(Entity e, skill_t skill, int xp)
{
	addRawXP(e, skill, xp * XPSCALE);
}

void SkillManager::addXP(Entity e, skill_t skill)
{
	//Default XP to add is 1
	addXP(e, skill, 1);
}

int SkillManager::getSkillLevel(Entity e, skill_t skill)
{
	int level = getBaseSkillLevel(e, skill);
	int penalty = getAttributePenalty(e, skill);

	return level - penalty;
}

skill_t SkillManager::getParentSkill(skill_t skill)
{
	//We simply have a global constant array for this (for now...)
	return PARENT_SKILLS[skill];
}

bool SkillManager::check(Entity e, skill_t skill)
{
	return check(e, skill, 0); //Do a check with no modifier
}

bool SkillManager::check(Entity e, skill_t skill, int modifier)
{
	int skill_level = getSkillLevel(e, skill) + modifier;
	// A check is successful if a 3d6 roll is less than or equal to the level
	_last_dos = skill_level - _dice.roll();
	return _last_dos >= 0;
}

int SkillManager::getLastDoS()
{
	return _last_dos;
}

void SkillManager::addRawXP(Entity e, skill_t skill, int raw_xp)
{
	//If getParentSkill doesn't give us our same skill back...
	skill_t parent = getParentSkill(skill);
	if(parent != skill)
	{
		//...then we have a parent skill, and add half our XP to it
		addRawXP(e, parent, raw_xp/2);
	}

	SkillComponent the_skill = getComponent(e, skill);

	the_skill.xp += raw_xp;

	//The threshold for the next rank is 10 times the next rank
	int threshold = (the_skill.ranks + 1) * LEVELUP * XPSCALE;
	if(the_skill.xp >= threshold)
	{
		the_skill.ranks += 1;
		the_skill.xp -= threshold;
	}

	setComponent(e, skill, the_skill);
}

int SkillManager::getBaseSkillLevel(Entity e, skill_t skill)
{
	int parent_level = 0;

	//If getParentSkill doesn't give us our same skill back...
	if(getParentSkill(skill) != skill)
	{
		//...then we have a parent skill
		parent_level = getBaseSkillLevel(e, PARENT_SKILLS[skill]);
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
		attrtype_t attribute = SKILL_ATTRIBUTES[skill];

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
		std::cout << "getAttributePenalty: " << attr.cur << '/' << attr.max;
		std::cout << " => " << (attr.max - attr.cur) * 5 / attr.max;
		std::cout << std::endl;
		return (attr.max - attr.cur) * 5 / attr.max;
	}

	return 0;
}


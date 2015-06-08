#include "entity/managers/SkillManager.h"

#define XPSCALE 1000
#define LEVELUP 10

const SkillComponent SkillManager::NULL_SKILL = { 0, 0 };

SkillManager::SkillManager()
{
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
	int parent_level = 0;

	//If getParentSkill doesn't give us our same skill back...
	if(getParentSkill(skill) != skill)
	{
		//...then we have a parent skill
		parent_level = getSkillLevel(e, PARENT_SKILLS[skill]);
	}

	int ranks = getComponent(e, skill).ranks;

	//Skill level is equal to ranks plus 1/2 parent skill's level
	///@todo Need to also account for a damaged attribute
	///@todo Need to accomodate "default skill"
	return ranks + (parent_level / 2);
}

skill_t SkillManager::getParentSkill(skill_t skill)
{
	//We simply have a global constant array for this (for now...)
	return PARENT_SKILLS[skill];
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


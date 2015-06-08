#include "entity/managers/SkillManager.h"

const SkillComponent SkillManager::NULL_SKILL = { 0, 0 };

SkillManager::SkillManager()
{
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
	return ranks + (parent_level / 2);
}

skill_t SkillManager::getParentSkill(skill_t skill)
{
	//We simply have a global constant array for this (for now...)
	return PARENT_SKILLS[skill];
}


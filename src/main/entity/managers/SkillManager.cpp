#include "entity/managers/SkillManager.h"

const SkillComponent SkillManager::NULL_SKILL = { 0, 0 };

SkillManager::SkillManager()
{
}

int SkillManager::getSkillLevel(Entity e, skill_t skill)
{
	int parent_level = 0;

	if(PARENT_SKILLS[skill] != skill)
	{
		parent_level = getSkillLevel(e, PARENT_SKILLS[skill]);
	}

	int ranks = getComponent(e, skill).ranks;

	//Skill level is equal to ranks plus 1/2 parent skill's level
	return ranks + (parent_level / 2);
}


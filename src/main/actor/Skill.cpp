#include <cstddef>

#include "actor/Skill.h"

Skill::Skill() : _dice(3, 6)
{
	_ranks = 0;
	_parent = NULL;
}

int Skill::getRanks()
{
	return _ranks;
}

void Skill::setRanks(int ranks)
{
	_ranks = ranks;
}

int Skill::getLevel()
{
	int level = _ranks;

	if(NULL != _parent)
	{
		level += _parent->getLevel()/2;
	}

	return level;
}

Skill* Skill::getParent()
{
	return _parent;
}

void Skill::setParent(Skill* parent)
{
	_parent = parent;
}

bool Skill::check()
{
	/**
	 * A Skill test is successful if a 3d6 roll is less than or equal to the
	 * Skill's level.
	 */
	return getLevel() >= _dice.roll();
}


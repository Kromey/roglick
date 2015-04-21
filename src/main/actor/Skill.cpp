#include <cstddef>

#include "actor/Skill.h"

Skill::Skill() : _dice(3, 6)
{
	_ranks = 0;
	_parent = NULL;
	_attr = NULL;
}

Attribute* Skill::getAttribute()
{
	return _attr;
}

void Skill::setAttribute(Attribute* attr)
{
	_attr = attr;
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
		//A Skill's level is its ranks plus half its parent's level (rounding down)
		level += _parent->getLevel()/2;
	}

	if(NULL != _attr)
	{
		//A Skill's level is further penalized by 1 point for each 20% loss of
		//its associated attribute; we multiply by 5 and assign to an int
		//because this gives us the number of 20% increments:
		//(x * 5 == x * 100 / 20).
		//We additionally use a small "fudge factor" afterwards to work around
		//floating-point imprecision.
		int attr_penalty = (1.0 - _attr->getCurRatio()) * 5.0 + 0.0000001;
		level -= attr_penalty;
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


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
		/**
		 * A Skill's level is its ranks plus half its parent's level (rounding down)
		 */
		level += _parent->getLevel()/2;
	}

	if(NULL != _attr)
	{
		/**
		 * A Skill is however penalized by 1 point for each *full* 20% increment
		 * that its associated Attribute has lost, e.g. an Attribute at 81% of
		 * its full value would incur no penalty for its associated Skills, but
		 * at 80% its Skills suffer a -1 penalty.
		 *
		 * To avoid the imprecision of floating-point arithmetic, however, we do
		 * our calculations with integers, which has the happy side effect of
		 * also eliminating the need for any round() or floor() calls:
		 *
		 *  AttrDmg = AttrMax - AttrCur //damage incurred to Attribute
		 *  Attr% = (AttrDmg * 100) / AttrMax //integer representation of percentage
		 *  Penalty = Attr% / 20 //integer math, so no floor'ing needed
		 *  Penalty = ((AttrDmg * 100) / AttrMax) / 20
		 *  Penalty = ((AttrDmg * 100) / 20) * 1/AttrMax
		 *  Penalty = (AttrDmg * 5) * 1/AttrMax
		 *  Penalty = (AttrDmg * 5) / AttrMax
		 */
		int attr_dmg = _attr->getMaxAttr() - _attr->getCurAttr();
		int attr_penalty = (attr_dmg * 5) / _attr->getMaxAttr();
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


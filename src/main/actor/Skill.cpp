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
		 * \f{eqnarray*}{
		 *  AttrDmg &=& AttrMax - AttrCur \\
		 *  AttrRatio &=& \frac{AttrDmg \times 100}{AttrMax} \\
		 *  Penalty &=& \frac{AttrRatio}{20} \\
		 *  Penalty &=& \frac{\frac{AttrDmg \times 100}{AttrMax}}{20} \\
		 *  Penalty &=& \frac{AttrDmg \times 100}{20} \times \frac{1}{AttrMax} \\
		 *  Penalty &=& (AttrDmg \times 5) \times \frac{1}{AttrMax} \\
		 *  Penalty &=& \frac{AttrDmg \times 5}{AttrMax}
		 * \f}
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

bool Skill::check(int modifier)
{
	/**
	 * A Skill test is successful if a 3d6 roll is less than or equal to the
	 * Skill's level.
	 */
	_last_check_dos = getLevel() + modifier - _dice.roll();
	return _last_check_dos >= 0;
}

int Skill::getDoS()
{
	return _last_check_dos;
}


#include "core/types.h"
#include "actor/Attribute.h"

Attribute::Attribute()
{
	_attr.max = Attribute::DEFAULT_ATTR;
	_attr.cur = _attr.max;
}

Attribute::Attribute(int max_attribute)
{
	_attr.max = max_attribute;
	_attr.cur = max_attribute;
}

damageable_t Attribute::getAttr()
{
	return _attr;
}

void Attribute::setAttr(damageable_t attr)
{
	_attr = attr;
}

int Attribute::getMaxAttr()
{
	return _attr.max;
}

void Attribute::setMaxAttr(int max_attribute)
{
	_attr.max = max_attribute;
}

int Attribute::getCurAttr()
{
	return _attr.cur;
}

void Attribute::setCurAttr(int cur_attribute)
{
	_attr.cur = cur_attribute;
}


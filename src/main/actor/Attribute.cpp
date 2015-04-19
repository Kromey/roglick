#include "actor/Attribute.h"

Attribute::Attribute()
{
	_max_attribute = Attribute::DEFAULT_ATTR;
	_cur_attribute = _max_attribute;
}

int Attribute::getMaxAttr()
{
	return _max_attribute;
}

void Attribute::setMaxAttr(int max_attribute)
{
	_max_attribute = max_attribute;
}

int Attribute::getCurAttr()
{
	return _cur_attribute;
}

void Attribute::setCurAttr(int cur_attribute)
{
	_cur_attribute = cur_attribute;
}


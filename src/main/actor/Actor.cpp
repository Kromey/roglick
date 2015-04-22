#include "actor/Actor.h"

const int Actor::ATTR_STR = 0;
const int Actor::ATTR_DEX = 1;
const int Actor::ATTR_STA = 3;
const int Actor::ATTR_INT = 4;
const int Actor::ATTR_PER = 5;
const int Actor::ATTR_ACU = 6;

Actor::Actor(char display, std::string name, int flags) : _name(name), _flags(flags)
{
	_display = display;
}

char Actor::getDisplay()
{
	return _display;
}

Attribute& Actor::getAttr(int attr_id)
{
	return _attrs[attr_id];
}


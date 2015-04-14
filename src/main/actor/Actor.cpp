#include "actor/Actor.h"

Actor::Actor(char display, std::string name, int flags) : _name(name), _flags(flags)
{
	_display = display;
}

char Actor::getDisplay()
{
	return _display;
}

#include "actor/Actor.h"

Actor::Actor(char display, std::string name, uint8_t flags) : _name(name), _flags(flags)
{
	_display = display;
}

char Actor::getDisplay()
{
	return _display;
}

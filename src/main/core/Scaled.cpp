#include "core/Scaled.h"

const int Scaled::SCALE_FACTOR = 2048;

Scaled::Scaled()
{
	_val = 0;
}

Scaled::Scaled(int val)
{
	_val = val * SCALE_FACTOR;
}

Scaled::operator int()
{
	return _val / SCALE_FACTOR;
}

Scaled Scaled::operator+(const Scaled& rhs)
{
	Scaled result;
	result._val = _val + rhs._val;
	return result;
}

Scaled Scaled::operator+(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this + s_rhs;
}

Scaled Scaled::operator-(const Scaled& rhs)
{
	Scaled result;
	result._val = _val - rhs._val;
	return result;
}

Scaled Scaled::operator-(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this - s_rhs;
}


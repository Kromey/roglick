#include "core/Scaled.h"

const int Scaled::SCALE_FACTOR = 2048;

Scaled::Scaled()
{
	_val = 0;
}

Scaled::Scaled(const int val)
{
	_val = val * SCALE_FACTOR;
}

Scaled::Scaled(const Scaled& rhs)
{
	_val = rhs._val;
}

Scaled::operator int()
{
	return _val / SCALE_FACTOR;
}

bool Scaled::operator==(const Scaled& rhs)
{
	return _val == rhs._val;
}

bool Scaled::operator==(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this == s_rhs;
}

bool Scaled::operator!=(const Scaled& rhs)
{
	return !(*this == rhs);
}

bool Scaled::operator!=(const int rhs)
{
	return !(*this == rhs);
}

bool Scaled::operator<(const Scaled& rhs)
{
	return _val < rhs._val;
}

bool Scaled::operator<(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this < s_rhs;
}

bool Scaled::operator>(const Scaled& rhs)
{
	return _val > rhs._val;
}

bool Scaled::operator>(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this > s_rhs;
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

Scaled Scaled::operator*(const Scaled& rhs)
{
	Scaled result;
	//AZ * BZ = C(Z*Z) -- therefore we have to divide out the extra factor
	result._val = (_val * rhs._val) / SCALE_FACTOR;
	return result;
}

Scaled Scaled::operator*(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this * s_rhs;
}

Scaled Scaled::operator/(const Scaled& rhs)
{
	Scaled result;
	//AZ / BZ = C -- therefore we have to multiply back in the factor
	//Multiply it in as early as possible for minimum truncation
	result._val = (_val * SCALE_FACTOR) / rhs._val;
	return result;
}

Scaled Scaled::operator/(const int rhs)
{
	Scaled s_rhs(rhs);
	return *this / s_rhs;
}


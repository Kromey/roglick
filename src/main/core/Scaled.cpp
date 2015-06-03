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

Scaled::Scaled(const double val)
{
	_val = val * (double)SCALE_FACTOR;
}

Scaled::Scaled(const Scaled& rhs)
{
	_val = rhs._val;
}

Scaled::operator int()
{
	return _val / SCALE_FACTOR;
}

Scaled::operator float()
{
	//A float's just a lower-precision double, just let the compiler handle that
	return (double)*this;
}

Scaled::operator double()
{
	return (double)_val / (double)SCALE_FACTOR;
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

bool Scaled::operator==(const double rhs)
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

bool Scaled::operator!=(const double rhs)
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

bool Scaled::operator<(const double rhs)
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

bool Scaled::operator>(const double rhs)
{
	Scaled s_rhs(rhs);
	return *this > s_rhs;
}

bool Scaled::operator<=(const Scaled& rhs)
{
	return *this < rhs || *this == rhs;
}

bool Scaled::operator<=(const int rhs)
{
	return *this < rhs || *this == rhs;
}

bool Scaled::operator<=(const double rhs)
{
	return *this < rhs || *this == rhs;
}

bool Scaled::operator>=(const Scaled& rhs)
{
	return *this > rhs || *this == rhs;
}

bool Scaled::operator>=(const int rhs)
{
	return *this > rhs || *this == rhs;
}

bool Scaled::operator>=(const double rhs)
{
	return *this > rhs || *this == rhs;
}

bool Scaled::operator!()
{
	return !_val;
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

Scaled Scaled::operator+(const double rhs)
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

Scaled Scaled::operator-(const double rhs)
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


#include "map/filters/Filter.h"

void Filter::setSeed(uint32_t seed)
{
	_seed = seed;
}

uint32_t Filter::getSeed()
{
	return _seed;
}


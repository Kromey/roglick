#include "map/generators/Generator.h"

void Generator::setSeed(uint32_t seed)
{
	_seed = seed;
}

uint32_t Generator::getSeed()
{
	return _seed;
}


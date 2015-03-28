#include "map/generators/Generator.h"

//Simplify the definitions
using namespace map;

void Generator::setSeed(uint32_t seed)
{
	_seed = seed;
}

uint32_t Generator::getSeed()
{
	return _seed;
}


#include "Rand.h"

Rand::Rand(int seed)
{
	regA = 0xACE1u;
}

int Rand::randbit()
{
	unsigned lsb = regA & 1;
	regA >>= 1;
	if(1 == lsb)
	{
		regA ^= 0xB400u;
	}

	return lsb;
}

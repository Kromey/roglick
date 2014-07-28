#include "Rand.h"

Rand::Rand(uint32_t seed)
{
	set_seed(seed);
}

void Rand::set_seed(uint32_t seed)
{
	if(0 == seed)
	{
		//No seed provided, provide one
		seed = 0xACE01u; //Nothing special about this value
	}

	//Seed registers
	regA = seed;
	regB = seed;
	regC = seed;

	//Shuffle in some entropy
	//Also ensures the three registers are fully different now
	for(int i = 0; i < 32; i++)
	{
		randbit();
	}
}

uint8_t Rand::randbit()
{
	return update_register(regA, LFRS_MASK_32)
		^ update_register(regB, LFRS_MASK_31)
		^ update_register(regC, LFRS_MASK_29);
}

uint32_t Rand::randn(uint32_t n)
{
	uint32_t bits = 0;

	if( 32 < n )
	{
		//We will only return 32 bits max, period
		n = 32;
	}

	for(uint32_t i = 0; i < n; i++)
	{
		bits <<= 1;
		bits |= randbit();
	}

	return bits;
}

uint32_t Rand::randint(uint32_t min, uint32_t max)
{
	uint32_t diff = max - min;

	//How many bits in diff?
	uint32_t bits = 1;
	uint32_t mask = 1;
	while( mask < diff )
	{
		mask <<= 1;
		mask |= 1;
		++bits;
	}

	//Now we'll get a random number of the appropriate bit size
	uint32_t number;
	while( diff < (number = randn(bits)) ) { };

	return min + number;
}

uint8_t Rand::update_register(uint32_t &reg, uint32_t mask)
{
	uint8_t lsb = reg & 1;
	reg >>= 1;

	if(1 == lsb)
	{
		reg ^= mask;
	}

	return lsb;
}


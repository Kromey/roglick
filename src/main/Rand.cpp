#include "Rand.h"

Rand::Rand(uint32_t seed)
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

int Rand::randbit()
{
	return rand_rega() ^ rand_regb() ^ rand_regc();
}

uint8_t Rand::rand_rega()
{
	uint8_t lsb = regA & 1;
	regA >>= 1;

	if(1 == lsb)
	{
		regA ^= LFRS_MASK_32;
	}

	return lsb;
}

uint8_t Rand::rand_regb()
{
	uint8_t lsb = regB & 1;
	regB >>= 1;

	if(1 == lsb)
	{
		regB ^= LFRS_MASK_31;
	}

	return lsb;
}

uint8_t Rand::rand_regc()
{
	uint8_t lsb = regC & 1;
	regC >>= 1;

	if(1 == lsb)
	{
		regC ^= LFRS_MASK_29;
	}

	return lsb;
}


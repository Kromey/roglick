#include "Rand.h"

Rand::Rand(uint32_t seed)
{
	if(0 == seed)
	{
		//No seed provided, provide one
		seed = 0xACE01u; //Nothing special about this value
	}

	//Seed regA with seed
	regA = seed;
	//Shuffle in some entropy
	for(int i = 0; i < 32; i++)
	{
		rand_rega();
	}

	//Now seed regB with regA
	regB = regA;
	//Shuffle in some entropy
	for(int i = 0; i < 32; i++)
	{
		rand_regb();
	}

	//Now seed regC with regB
	regC = regB & 0x3FFFFFFFu;
	//Shuffle in some entropy
	for(int i = 0; i < 32; i++)
	{
		rand_regc();
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
		regC ^= LFRS_MASK_30;
	}

	return lsb;
}


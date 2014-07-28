#include "Rand.h"

Rand::Rand()
{
	//Initialize to the default seed
	setSeed(0);
}

Rand::Rand(uint32_t seed)
{
	//Initialize to the provided seed
	setSeed(seed);
}

Rand::Rand(const Rand& src)
{
	_reg_a = src._reg_a;
	_reg_b = src._reg_b;
	_reg_c = src._reg_c;
}

Rand::Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c)
{
	if(!setRegisters(src_reg_a, src_reg_b, src_reg_c))
	{
		//If we fail to set the registers, fall back to our default seed
		setSeed(0);
	}
}

void Rand::setSeed(uint32_t seed)
{
	if(0 == seed)
	{
		//No seed provided, provide one
		seed = 0xACE01u; //Nothing special about this value
	}

	//Seed registers
	_reg_a = seed;
	_reg_b = seed;
	_reg_c = seed;

	//Shuffle in some entropy
	//Also ensures the three registers are fully different now
	for(int i = 0; i < 32; i++)
	{
		randBit();
	}
}

bool Rand::setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c)
{
	if(0 == src_reg_a || 0 == src_reg_b || 0 == src_reg_c)
	{
		return false; //We cannot set registers to 0
	}

	_reg_a = src_reg_a;
	_reg_b = src_reg_b;
	_reg_c = src_reg_c;

	return true;
}

void Rand::getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c)
{
	dst_reg_a = _reg_a;
	dst_reg_b = _reg_b;
	dst_reg_c = _reg_c;
}

uint8_t Rand::randBit()
{
	return updateRegister(_reg_a, Rand::LFRS_MASK_32)
		 ^ updateRegister(_reg_b, Rand::LFRS_MASK_31)
		 ^ updateRegister(_reg_c, Rand::LFRS_MASK_29);
}

uint32_t Rand::randN(uint32_t n)
{
	uint32_t bits = 0;

	if(32 < n)
	{
		//We will only return 32 bits max, period
		n = 32;
	}

	for(uint32_t i = 0; i < n; i++)
	{
		bits <<= 1;
		bits |= randBit();
	}

	return bits;
}

uint32_t Rand::randInt(uint32_t min, uint32_t max)
{
	uint32_t diff = max - min;

	//How many bits in diff?
	uint32_t bits = 1;
	uint32_t mask = 1;
	while(mask < diff)
	{
		mask <<= 1;
		mask |= 1;
		++bits;
	}

	//Now we'll get a random number of the appropriate bit size
	uint32_t number;
	while(diff < (number = randN(bits))) { };

	return min + number;
}

uint8_t Rand::updateRegister(uint32_t &reg, uint32_t mask)
{
	uint8_t lsb = reg & 1;
	reg >>= 1;

	if(1 == lsb)
	{
		reg ^= mask;
	}

	return lsb;
}


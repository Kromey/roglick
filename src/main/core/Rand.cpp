/**
 * File: Rand.cpp
 * Provides the implementation for the Rand object
 *
 * Full method and member documentation can be found in <Rand.h>.
 *
 * Version:
 *   1.0
 *
 * Author:
 *   Travis Veazey
 *
 * Date:
 *   2014-08-14
 */
#include <utility>
#include "core/Rand.h"

//Default constructor
Rand::Rand()
{
	//Initialize to the default seed
	setSeed(0);
}

//Seed constructor
Rand::Rand(uint32_t seed)
{
	//Initialize to the provided seed
	setSeed(seed);
}

//Copy constructor
Rand::Rand(const Rand& src)
{
	_reg_a = src._reg_a;
	_reg_b = src._reg_b;
	_reg_c = src._reg_c;
}

//Register constructor
Rand::Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c)
{
	if(!setRegisters(src_reg_a, src_reg_b, src_reg_c))
	{
		//If we fail to set the registers, fall back to our default seed
		setSeed(0);
	}
}

//Assignment operator
Rand& Rand::operator=(const Rand& rhs)
{
	Rand tmp(rhs);

	std::swap(_reg_a, tmp._reg_a);
	std::swap(_reg_b, tmp._reg_b);
	std::swap(_reg_c, tmp._reg_c);

	return *this;
}

//(Re)Set the internal state to the specified seed.
void Rand::setSeed(uint32_t seed)
{
	if(0 == seed)
	{
		//No seed provided, provide one
		seed = 0xACE01u; //Nothing special about this value
	}

	//Seed registers with our seed value
	if(!setRegisters(seed, seed, seed))
	{
		//We failed, means at least one register got nothing in the low bits
		if(!setRegisters(seed, seed, seed>>(REG_WIDTH_INT-REG_WIDTH_C)))
		{
			//Failed again, means both lower register got nothing
			//This one won't fail because we already know it's a non-0 seed
			setRegisters(seed, seed>>(REG_WIDTH_INT-REG_WIDTH_B), seed>>(REG_WIDTH_INT-REG_WIDTH_C));
		}
	}

	//Shuffle in some entropy
	//Also ensures the three registers are fully different now
	for(int i = 0; i < 32; i++)
	{
		randBit();
	}
}

//Set the internal register state directly
bool Rand::setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c)
{
	//Mask the inputs to fit into our registers
	src_reg_a &= REG_MASK_A;
	src_reg_b &= REG_MASK_B;
	src_reg_c &= REG_MASK_C;

	if(0 == src_reg_a || 0 == src_reg_b || 0 == src_reg_c)
	{
		return false; //We cannot set registers to 0
	}

	_reg_a = src_reg_a;
	_reg_b = src_reg_b;
	_reg_c = src_reg_c;

	return true;
}

//Retrieve the internal register state
void Rand::getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c)
{
	dst_reg_a = _reg_a;
	dst_reg_b = _reg_b;
	dst_reg_c = _reg_c;
}

//Get a single random bit
uint8_t Rand::randBit()
{
	return updateRegister(_reg_a, Rand::LFRS_MASK_A)
		 ^ updateRegister(_reg_b, Rand::LFRS_MASK_B)
		 ^ updateRegister(_reg_c, Rand::LFRS_MASK_C);
}

/**
 * @brief  Return n random bits as an integer
 *
 * This method will only return a maximum of 32 bits; any supplied value of n
 * greater than that will be treated as if it were 32.
 *
 * @param n Number of bits to generate
 *
 * @return Generated bits returned as an integer
 */
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

/**
 * @brief  Return a random integer between min and max (inclusive)
 *
 * @param min Minimum value of returned integer
 * @param max Maximum value of returned integer
 *
 * @return The generated integer
 */
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

/**
 * @brief  Update the specified register, and return the next bit in the sequence
 *
 * @param reg The register to update
 * @param mask The mask to apply to it
 *
 * @return The next bit in the sequence
 */
uint8_t Rand::updateRegister(uint32_t& reg, uint32_t mask)
{
	uint8_t lsb = reg & 1;
	reg >>= 1;

	if(1 == lsb)
	{
		reg ^= mask;
	}

	return lsb;
}

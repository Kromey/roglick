/**
 * @file Rand.cpp
 * @brief Implementation of the Rand object
 * @author Travis Veazey
 * @version 1.0
 * @date 2014-07-28
 */
#include "Rand.h"

/**
 * @brief  Default constructor
 */
Rand::Rand()
{
	//Initialize to the default seed
	setSeed(0);
}

/**
 * @brief  Seeded constructor to set generator's initial state
 *
 * @param seed
 */
Rand::Rand(uint32_t seed)
{
	//Initialize to the provided seed
	setSeed(seed);
}

/**
 * @brief  Copy constructor
 *
 * @param src Rand object to copy
 */
Rand::Rand(const Rand& src)
{
	_reg_a = src._reg_a;
	_reg_b = src._reg_b;
	_reg_c = src._reg_c;
}

/**
 * @brief  Constructor to directly set internal register states
 *
 * @param src_reg_a Value for 32-bit register A
 * @param src_reg_b Value for 31-bit register B
 * @param src_reg_c Value for 29-bit register C
 */
Rand::Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c)
{
	if(!setRegisters(src_reg_a, src_reg_b, src_reg_c))
	{
		//If we fail to set the registers, fall back to our default seed
		setSeed(0);
	}
}

/**
 * @brief  Resets the generator to the state defined by the supplied seed
 *
 * @param seed Seed to set the state to
 */
void Rand::setSeed(uint32_t seed)
{
	if(0 == seed)
	{
		//No seed provided, provide one
		seed = 0xACE01u; //Nothing special about this value
	}

	//Seed registers with our seed value
	setRegisters(seed, seed, seed);

	//Shuffle in some entropy
	//Also ensures the three registers are fully different now
	for(int i = 0; i < 32; i++)
	{
		randBit();
	}
}

/**
 * @brief  Directly set internal register state
 *
 * If any of the supplied register values is 0, this method will return false
 * and leave the register states unchanged.
 *
 * @param src_reg_a Value for 32-bit register A
 * @param src_reg_b Value for 31-bit register B
 * @param src_reg_c Value for 29-bit register C
 *
 * @return True on success, false on failure
 */
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

/**
 * @brief  Retrieve the states of all three internal registers
 *
 * @param[out] dst_reg_a Value of register A
 * @param[out] dst_reg_b Value of register B
 * @param[out] dst_reg_c Value of register C
 */
void Rand::getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c)
{
	dst_reg_a = _reg_a;
	dst_reg_b = _reg_b;
	dst_reg_c = _reg_c;
}

/**
 * @brief  Return a random bit
 *
 * @return A random bit, returned as an integer
 */
uint8_t Rand::randBit()
{
	return updateRegister(_reg_a, Rand::LFRS_MASK_32)
		 ^ updateRegister(_reg_b, Rand::LFRS_MASK_31)
		 ^ updateRegister(_reg_c, Rand::LFRS_MASK_29);
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


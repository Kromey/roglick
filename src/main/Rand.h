#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

#define LFRS_MASK_32 0x800CE000u
#define LFRS_MASK_31 0x4004F000u
#define LFRS_MASK_30 0x20065400u

class Rand
{
	public:
		//Constructor allows initializing the state
		Rand(uint32_t seed = 0);

		//Returns a single random bit
		int randbit();
	private:
		//Registers for storing generator state
		//A is 32 bits; B is 31 bits; and C is 30 bits
		uint32_t regA;
		uint32_t regB;
		uint32_t regC;

		//Methods for retrieving each register
		uint8_t rand_rega();
		uint8_t rand_regb();
		uint8_t rand_regc();
};

#endif

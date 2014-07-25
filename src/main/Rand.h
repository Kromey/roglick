#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

class Rand
{
	public:
		//Constructor allows initializing the state
		Rand(uint32_t seed = 0);

		//Returns a single random bit
		uint8_t randbit();
	private:
		//Registers for storing generator state
		//A is 32 bits; B is 31 bits; and C is 29 bits
		uint32_t regA;
		uint32_t regB;
		uint32_t regC;

		//Methods for retrieving each register
		uint8_t rand_rega();
		uint8_t rand_regb();
		uint8_t rand_regc();
};

/**
 * These masks implement the equivalent Galois LFSRs that Bruce Schneier
 * proposes for his 32-bit pseudo-random sequence generator.
 * https://www.schneier.com/paper-pseudorandom-sequence.html
 * Galois LFSRs are equivalent to simple LFSRs, just phase-shifted.
 * http://www.newwaveinstruments.com/resources/articles/m_sequence_linear_feedback_shift_register_lfsr.htm
 */
#define LFRS_MASK_32 0x80000057u
#define LFRS_MASK_31 0x40000004u
#define LFRS_MASK_29 0x10000002u

#endif

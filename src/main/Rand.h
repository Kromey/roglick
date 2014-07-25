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
		//Returns n random bits
		uint32_t randn(uint32_t n);
		//Return an integer between min and max (inclusive)
		uint32_t randint(uint32_t min, uint32_t max);
		//Return an integer between 0 and max (inclusive)
		uint32_t randint(uint32_t max) { return randint(0, max); };

		//Convenience methods for common bit-lengths
		uint32_t rand8() { return randn(8); };
		uint32_t rand16() { return randn(16); };
		uint32_t rand32() { return randn(32); };
	private:
		//Registers for storing generator state
		//A is 32 bits; B is 31 bits; and C is 29 bits
		uint32_t regA;
		uint32_t regB;
		uint32_t regC;

		//Update the register and return the next bit from the sequence
		uint8_t update_register(uint32_t &reg, uint32_t mask);
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

#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

class Rand
{
	public:
		//Constructors
		Rand(); //Default constructor
		Rand(uint32_t seed); //Constructor with a single seed
		Rand(const Rand& src); //Copy constructor
		Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c); //Set internal state

		//Seed the generator
		void setSeed(uint32_t seed);

		//Set internal state
		bool setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);
		//Get internal state
		void getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c);

		//Returns a single random bit
		uint8_t randBit();
		//Returns n random bits
		uint32_t randN(uint32_t n);
		//Return an integer between min and max (inclusive)
		uint32_t randInt(uint32_t min, uint32_t max);
		//Return an integer between 0 and max (inclusive)
		uint32_t randInt(uint32_t max) { return randInt(0, max); };

		//Convenience methods for common bit-lengths
		uint32_t rand8() { return randN(8); };
		uint32_t rand16() { return randN(16); };
		uint32_t rand32() { return randN(32); };
	private:
		//Registers for storing generator state
		//A is 32 bits; B is 31 bits; and C is 29 bits
		uint32_t _reg_a;
		uint32_t _reg_b;
		uint32_t _reg_c;

		//Update the register and return the next bit from the sequence
		uint8_t updateRegister(uint32_t &reg, uint32_t mask);

		/**
		 * These masks implement the equivalent Galois LFSRs that Bruce Schneier
		 * proposes for his 32-bit pseudo-random sequence generator.
		 * https://www.schneier.com/paper-pseudorandom-sequence.html
		 * Galois LFSRs are equivalent to simple LFSRs, just phase-shifted.
		 * http://www.newwaveinstruments.com/resources/articles/m_sequence_linear_feedback_shift_register_lfsr.htm
		 */
		static const uint32_t LFRS_MASK_32 = 0x80000057u;
		static const uint32_t LFRS_MASK_31 = 0x40000004u;
		static const uint32_t LFRS_MASK_29 = 0x10000002u;
};


#endif

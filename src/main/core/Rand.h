/**
 * File: Rand.h
 * Provides the declaration for the Rand object
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
#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

/**
 * Class: Rand
 *
 * A fast PRNG that is consistent across platforms and compilers.
 *
 * Rand implements an LFSR-based random number generator, utilizing a trio of
 * mutually-prime registers to greatly augment the pool length before the cycle
 * repeats -- somewhere on the order of one billion billion billion bits.
 */
class Rand
{
	public:
		/**
		 * Constructors: Rand
		 *
		 * Rand()         - Default constructor, initializes the object to the
		 *                  default seed.
		 * Rand(uint32_t) - Seed constructor, allows the seed to be specified.
		 *                  See <setSeed>.
		 * Rand(Rand)     - Copy constructor, duplicates the internal state of
		 *                  the copied object.
		 * Rand(uint32_t, uint32_t, uint32_t) - This constructor allows the
		 *                  internal register state to be set directorly.
		 *                  See <setRegisters>, except on failure this will
		 *                  fall back to using the default seed.
		 */
		Rand();
		Rand(uint32_t seed);
		Rand(const Rand& src);
		Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);

		/**
		 * Destructor: ~Rand
		 *
		 * Destructor does nothing.
		 */
		~Rand() { };

		/**
		 * Operator: operator=
		 *
		 * Assignment operator provides an exact duplicate of the source object's
		 * internal state.
		 *
		 * Parameters:
		 *
		 *   rhs - The source Rand object
		 */
		Rand& operator=(const Rand& rhs);

		/**
		 * Method: setSeed
		 *
		 * (Re)Initializes the Rand object to the provided seed.
		 *
		 * *NOTICE:* A seed value of 0 will be replaced with a default value
		 * instead.
		 *
		 * Parameters:
		 *
		 *   seed - The seed
		 */
		void setSeed(uint32_t seed);

		/**
		 * Method: setRegisters
		 *
		 * Directly set internal register state.
		 *
		 * If any of the supplied register values is 0, this method will return
		 * false and leave the register states unchanged.
		 *
		 * Parameters:
		 *
		 *   src_reg_a - Value for 32-bit register A
		 *   src_reg_b - Value for 31-bit register B
		 *   src_reg_c - Value for 29-bit register C
		 *
		 * Returns:
		 *
		 *   True on success.
		 */
		bool setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);

		/**
		 * Method: getRegisters
		 *
		 * Retrieve the states of all three internal registers
		 *
		 * Parameters:
		 *
		 *   dst_reg_a (out) - Value of register A
		 *   dst_reg_b (out) - Value of register B
		 *   dst_reg_c (out) - Value of register C
		 */
		void getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c);

		/**
		 * Method: randBit
		 *
		 * Return a random bit
		 *
		 * Returns:
		 *
		 *   A random bit, returned as an unsigned integer (uint8_t)
		 */
		uint8_t randBit();

		/**
		 * Method: randN
		 *
		 * Generate n random bits.
		 *
		 * This method will only generate a maximum of 32 bits in a single
		 * sequence; any n larger than 32 will be silently reduced to 32.
		 *
		 * Parameters:
		 *
		 *   n - Number of bits to generate
		 *
		 * Returns:
		 *
		 *   The generated bit sequence as an unsigned integer (uint32_t)
		 */
		uint32_t randN(uint32_t n);

		/**
		 * Method: rand8
		 *
		 * A convenience method that is the same as calling <randN> with a
		 * parameter of 8.
		 *
		 */
		uint32_t rand8() { return randN(8); };

		/**
		 * Method: rand16
		 *
		 * A convenience method that is the same as calling <randN> with a
		 * parameter of 16.
		 *
		 */
		uint32_t rand16() { return randN(16); };

		/**
		 * Method: rand32
		 *
		 * A convenience method that is the same as calling <randN> with a
		 * parameter of 32.
		 *
		 */
		uint32_t rand32() { return randN(32); };

		/**
		 * Method: randInt(min, max)
		 *
		 * Generate a random integer between min and max (inclusive).
		 *
		 * Parameters:
		 *
		 *   min - Minimum value of generated integer
		 *   max - Maximum value of generated integer
		 *
		 * Returns:
		 *
		 *   Generated integer
		 */
		uint32_t randInt(uint32_t min, uint32_t max);

		/**
		 * Method: randInt(max)
		 *
		 * Generate a random integer between 0 and max (inclusive).
		 *
		 * This method is identical to calling <randInt(min, max)> with a
		 * min parameter of 0; see that method for complete documentation.
		 */
		uint32_t randInt(uint32_t max) { return randInt(0, max); };

	private:
		/**
		 * Variables: _reg_*
		 *
		 * These members store the internal register states for each of the 3
		 * Galois LFSRs uses in this generator.
		 *
		 * _reg_a - 32-bit register
		 * _reg_b - 31-bit register
		 * _reg_c - 29-bit register
		 */
		uint32_t _reg_a;
		uint32_t _reg_b;
		uint32_t _reg_c;

		/**
		 * Method: updateRegister
		 *
		 * Updates the supplied register and returns the generated bit.
		 *
		 * Parameters:
		 *
		 *   reg (inout) - The register to update
		 *   mask        - The bitmask to use to update the register
		 *
		 * Returns:
		 *
		 *   The next bit in the sequence.
		 */
		uint8_t updateRegister(uint32_t& reg, uint32_t mask);

		/**
		 * Constants: REG_WIDTH_*
		 *
		 * These constants describe the bit-width of each of our registers. They
		 * are selected to be mutually-prime and thus ensure that the overall
		 * pool is the product of all 3, rather than a smaller factor thereof.
		 *
		 * REG_WIDTH_A   - 32-bit register
		 * REG_WIDTH_B   - 31-bit register
		 * REG_WIDTH_C   - 29-bit register
		 * REG_WIDTH_INT - Width of the internal storage used for the registers
		 */
		static const uint32_t REG_WIDTH_A = 32;
		static const uint32_t REG_WIDTH_B = 31;
		static const uint32_t REG_WIDTH_C = 29;
		static const uint32_t REG_WIDTH_INT = 32;

		/**
		 * Constants: LFRS_MASK_*
		 *
		 * These masks implement the equivalent Galois LFSRs that Bruce Schneier
		 * proposes for his 32-bit pseudo-random sequence generator.
		 * https://www.schneier.com/paper-pseudorandom-sequence.html
		 * Galois LFSRs are equivalent to simple LFSRs, just phase-shifted.
		 * http://www.newwaveinstruments.com/resources/articles/m_sequence_linear_feedback_shift_register_lfsr.htm
		 *
		 * LFRS_MASK_A - Mask for the 32-bit register
		 * LFRS_MASK_B - Mask for the 31-bit register
		 * LFRS_MASK_C - Mask for the 29-bit register
		 */
		static const uint32_t LFRS_MASK_A = 0x80000057u;
		static const uint32_t LFRS_MASK_B = 0x40000004u;
		static const uint32_t LFRS_MASK_C = 0x10000002u;

		/**
		 * Constants: REG_MASK_*
		 *
		 * These masks exist to prevent the registers from exceeding their
		 * logical bit-widths (32, 31, and 29 bits, respectively).
		 *
		 * REG_MASK_A - Mask for 32 bits
		 * REG_MASK_B - Mask for 31 bits
		 * REG_MASK_C - Mask for 29 bits
		 */
		static const uint32_t REG_MASK_A = 0xFFFFFFFFu;
		static const uint32_t REG_MASK_B = 0x7FFFFFFFu;
		static const uint32_t REG_MASK_C = 0x1FFFFFFFu;
};


#endif

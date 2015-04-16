#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

/**
 * A fast PRNG that is consistent across platforms and compilers.
 *
 * Rand implements an LFSR-based random number generator, utilizing a trio of
 * mutually-prime registers to greatly augment the pool length before the cycle
 * repeats -- somewhere on the order of one billion billion billion bits.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class Rand
{
	public:
		/**
		 * Default constructor, initializes the object to the default seed.
		 */
		Rand();
		/**
		 * Seed constructor, allows the seed to be specified.
		 *
		 * @see setSeed
		 * @param seed The value to seed the PRNG to.
		 */
		Rand(uint32_t seed);
		/**
		 * Copy constructor, duplicates the internal state of the copied PRNG.
		 *
		 * @param src The Rand object to copy.
		 */
		Rand(const Rand& src);
		/**
		 * This constructor allows the internal registers to be set directly.
		 *
		 * @see setRegister
		 * @param src_reg_a State for register A.
		 * @param src_reg_b State for register B.
		 * @param src_reg_c State for register C.
		 */
		Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);

		/**
		 * Assignment operator provides an exact duplicate of the source object's
		 * internal state.
		 *
		 * @param rhs The object to be duplicated.
		 *
		 * @return A reference to this object after assignment.
		 */
		Rand& operator=(const Rand& rhs);

		/**
		 * (Re)Initializes the Rand object to the provided seed.
		 *
		 * *NOTICE:* A seed value of 0 will be replaced with a default value
		 * instead.
		 *
		 * @param seed The seed.
		 */
		void setSeed(uint32_t seed);

		/**
		 * Directly set internal register state.
		 *
		 * If any of the supplied register values is 0, this method will return
		 * false and leave the register states unchanged.
		 *
		 * @param src_reg_a Value for 32-bit register A.
		 * @param src_reg_b Value for 31-bit register B.
		 * @param src_reg_c Value for 29-bit register C.
		 *
		 * @return True on success.
		 */
		bool setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);

		/**
		 * Retrieve the states of all three internal registers.
		 *
		 * @param[out] dst_reg_a Value of register A.
		 * @param[out] dst_reg_b Value of register B.
		 * @param[out] dst_reg_c Value of register C.
		 */
		void getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c);

		/**
		 * Return a random bit.
		 *
		 * @return A random bit, returned as an unsigned integer (uint8_t).
		 */
		uint8_t randBit();

		/**
		 * Generate n random bits.
		 *
		 * This method will only generate a maximum of 32 bits in a single
		 * sequence; any n larger than 32 will be silently reduced to 32.
		 *
		 * @param n Number of bits to generate.
		 *
		 * @return The generated bit sequence as an unsigned integer (uint32_t).
		 */
		uint32_t randN(uint32_t n);

		/**
		 * A convenience method that is the same as calling randN with a
		 * parameter of 8.
		 *
		 * @see randN.
		 * @return 8 random bits.
		 */
		uint32_t rand8() { return randN(8); };

		/**
		 * A convenience method that is the same as calling randN with a
		 * parameter of 16.
		 *
		 * @see randN.
		 * @return 16 random bits.
		 */
		uint32_t rand16() { return randN(16); };

		/**
		 * A convenience method that is the same as calling randN with a
		 * parameter of 32.
		 *
		 * @see randN.
		 * @return 32 random bits.
		 */
		uint32_t rand32() { return randN(32); };

		/**
		 * Generate a random integer between min and max (inclusive).
		 *
		 * @param min Minimum value of generated integer.
		 * @param max Maximum value of generated integer.
		 *
		 * @return Generated integer.
		 */
		uint32_t randInt(uint32_t min, uint32_t max);

		/**
		 * Generate a random integer between 0 and max (inclusive).
		 *
		 * This method is identical to calling randInt(min, max) with a
		 * min parameter of 0.
		 *
		 * @param max Maximum value of generated integer.
		 *
		 * @return Generated integer.
		 */
		uint32_t randInt(uint32_t max) { return randInt(0, max); };

		/**
		 * Generate a random floating-point number between 0.0 and 1.0.
		 *
		 * @return Random floating-point value.
		 */
		double randFloat();

		/**
		 * Maximum possible integer value that Rand can generate.
		 */
		static const uint32_t RAND_MAX_INT = 0xFFFFFFFFu;

	private:
		/**
		 * 32-bit internal state register.
		 */
		uint32_t _reg_a;
		/**
		 * 31-bit internal state register.
		 */
		uint32_t _reg_b;
		/**
		 * 29-bit internal state register.
		 */
		uint32_t _reg_c;

		/**
		 * Updates the supplied register and returns the generated bit.
		 *
		 * @param[inout] reg The register to update.
		 * @param mask The bitmask to use to update the register.
		 *
		 * @return The next bit in the sequence.
		 */
		uint8_t updateRegister(uint32_t& reg, uint32_t mask);

		/**
		 * Bit-width of register A.
		 */
		static const uint32_t REG_WIDTH_A = 32;
		/**
		 * Bit-width of register B.
		 */
		static const uint32_t REG_WIDTH_B = 31;
		/**
		 * Bit-width of register C.
		 */
		static const uint32_t REG_WIDTH_C = 29;
		/**
		 * Bit-width of the internal storage used for the registers, helps with
		 * the masking and the math used internally.
		 */
		static const uint32_t REG_WIDTH_INT = 32;

		/**
		 * These masks implement the equivalent Galois LFSRs that Bruce Schneier
		 * proposes for <his 32-bit pseudo-random sequence generator at
		 * https://www.schneier.com/paper-pseudorandom-sequence.html>.
		 *
		 * According to <some smart people at New Wave Instruments at
		 * http://www.newwaveinstruments.com/resources/articles/m_sequence_linear_feedback_shift_register_lfsr.htm>,
		 * Galois LFSRs are equivalent to simple LFSRs, just phase-shifted.
		 *
		 * LFRS_MASK_A - Mask for the 32-bit register
		 * LFRS_MASK_B - Mask for the 31-bit register
		 * LFRS_MASK_C - Mask for the 29-bit register
		 */
		static const uint32_t LFRS_MASK_A = 0x80000057u;
		static const uint32_t LFRS_MASK_B = 0x40000004u;
		static const uint32_t LFRS_MASK_C = 0x10000002u;

		/**
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

		/**
		 * This value is the default seed for the generator. This is a purely
		 * arbitrary value.
		 */
		static const uint32_t DEFAULT_SEED = 0xACE01u;
};


#endif

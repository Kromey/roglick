/**
 * @file Rand.h
 * @brief This header defines the Rand object, an LFSR-based PRNG
 * @author Travis Veazey
 * @version 1.0
 * @date 2014-07-28
 */
#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

/**
 * @brief  Rand implements an LFSR-based random number generator.
 */
class Rand
{
	public:
		//Constructors
		/**
		 * @brief  Default constructor
		 */
		Rand();
		/**
		 * @brief  Seed constructor
		 *
		 * @param seed The seed to use for the new Rand object
		 */
		Rand(uint32_t seed);
		/**
		 * @brief  Copy constructor; the new object will have identical state
		 *
		 * @param src The Rand object to copy
		 */
		Rand(const Rand& src);
		/**
		 * @brief  Constructor to set individual registers directly
		 *
		 * @param src_reg_a Value to set the 32-bit register A to
		 * @param src_reg_b Value to set the 31-bit register B to
		 * @param src_reg_c Value to set the 29-bit register C to
		 */
		Rand(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);
		/**
		 * @brief  Destructor
		 */
		~Rand() { };

		/**
		 * @brief  Assignment operator
		 *
		 * @param rhs The source Rand object
		 *
		 * @return 
		 */
		Rand& operator=(const Rand& rhs);

		/**
		 * @brief  Seed the generator
		 *
		 * @param seed The seed to resest the generator to
		 */
		void setSeed(uint32_t seed);

		/**
		 * @brief  Set the internal registers directly
		 *
		 * @param src_reg_a Value to set the 32-bit register A to
		 * @param src_reg_b Value to set the 31-bit register B to
		 * @param src_reg_c Value to set the 29-bit register C to
		 *
		 * @return True on success, false on failure
		 */
		bool setRegisters(uint32_t src_reg_a, uint32_t src_reg_b, uint32_t src_reg_c);
		/**
		 * @brief  Get the current state of the internal registers
		 *
		 * @param[out] dst_reg_a Value in 32-bit register A
		 * @param[out] dst_reg_b Value in 31-bit register B
		 * @param[out] dst_reg_c Value in 29-bit register C
		 */
		void getRegisters(uint32_t& dst_reg_a, uint32_t& dst_reg_b, uint32_t& dst_reg_c);

		/**
		 * @brief  Generate a random bit
		 *
		 * @return The generated bit
		 */
		uint8_t randBit();
		/**
		 * @brief  Generate n random bits
		 *
		 * @param n Number of bits to generate
		 *
		 * @return The generated bits as an integer
		 */
		uint32_t randN(uint32_t n);
		/**
		 * @brief  Generate a random integer between min and max (inclusive)
		 *
		 * @param min Minimum value of generated integer
		 * @param max Maximum value of generated integer
		 *
		 * @return Generated integer
		 */
		uint32_t randInt(uint32_t min, uint32_t max);
		/**
		 * @brief  Generate a random integer between 0 and max (inclusive)
		 *
		 * @param max Maximum value of generated integer
		 *
		 * @return Generated integer
		 */
		uint32_t randInt(uint32_t max) { return randInt(0, max); };

		/**
		 * @brief  Generate 8 random bits
		 *
		 * @return The generated bits as an integer
		 */
		uint32_t rand8() { return randN(8); };
		/**
		 * @brief  Generate 16 random bits
		 *
		 * @return The generated bits as an integer
		 */
		uint32_t rand16() { return randN(16); };
		/**
		 * @brief  Generate 32 random bits
		 *
		 * @return The generated bits as an integer
		 */
		uint32_t rand32() { return randN(32); };
	private:
		/**
		 * @brief  32-bit internal state register
		 */
		uint32_t _reg_a;
		/**
		 * @brief  31-bit internal state register
		 */
		uint32_t _reg_b;
		/**
		 * @brief  29-bit internal state register
		 */
		uint32_t _reg_c;

		/**
		 * @brief  Updates the supplied register and returns the generated bit
		 *
		 * @param reg The register to update
		 * @param mask The bitmask to use to update the register
		 *
		 * @return The next bit in the sequence from this register
		 */
		uint8_t updateRegister(uint32_t& reg, uint32_t mask);

		/**
		 * These constants describe the bit-width of each of our registers. They
		 * are selected to be mutually-prime and thus ensure that the overall
		 * pool is the product of all 3, rather than a smaller factor thereof.
		 */
		static const uint32_t REG_WIDTH_A = 32;
		static const uint32_t REG_WIDTH_B = 31;
		static const uint32_t REG_WIDTH_C = 29;
		//Width of the internal storage of the registers
		static const uint32_t REG_WIDTH_INT = 32;

		/**
		 * These masks implement the equivalent Galois LFSRs that Bruce Schneier
		 * proposes for his 32-bit pseudo-random sequence generator.
		 * https://www.schneier.com/paper-pseudorandom-sequence.html
		 * Galois LFSRs are equivalent to simple LFSRs, just phase-shifted.
		 * http://www.newwaveinstruments.com/resources/articles/m_sequence_linear_feedback_shift_register_lfsr.htm
		 */
		static const uint32_t LFRS_MASK_A = 0x80000057u;
		static const uint32_t LFRS_MASK_B = 0x40000004u;
		static const uint32_t LFRS_MASK_C = 0x10000002u;

		/**
		 * These masks exist to prevent the registers from exceeding their
		 * logical bit-widths (32, 31, and 29 bits, respectively).
		 */
		static const uint32_t REG_MASK_A = 0xFFFFFFFFu;
		static const uint32_t REG_MASK_B = 0x7FFFFFFFu;
		static const uint32_t REG_MASK_C = 0x1FFFFFFFu;
};


#endif

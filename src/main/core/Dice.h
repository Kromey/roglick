#ifndef DICE_H_
#define DICE_H_

#include <stdint.h>
#include "core/Rand.h"

/**
 * A dice-rolling object.
 *
 * Dice provides a lightweight wrapper around the Rand object convenient for
 * quickly rolling any number of n-sided dice. Dice objects manage a quasi-
 * shared seed that is reinitialized to a random value each time an object is
 * created, ensuring that Dice objects always produce different sequences of
 * results.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class Dice : protected Rand
{
	public:
		/**
		 * Creates an instance of the Dice object representing n d-sided dice.
		 *
		 * @param n The number of dice to roll
		 * @param d How many sides on each die
		 */
		Dice(uint32_t n = 1, uint32_t d = 6);

		/**
		 * Rolls the n d-sided dice and returns the sum.
		 *
		 * @return The roll result.
		 */
		uint32_t roll();

	private:
		/**
		 * This member stores how many dice we are rolling.
		 */
		uint32_t _n;

		/**
		 * This member stores the number of sides on each die.
		 */
		uint32_t _d;

		/**
		 * A static seed that is replaced every time a Dice object is
		 * instantiated guarantees that we will always have unique rolls from
		 * our Dice objects.
		 */
		static uint32_t _dice_seed;
};

#endif
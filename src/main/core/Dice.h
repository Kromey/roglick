/**
 * A dice-rolling object.
 *
 * Dice provides a lightweight rapper around the Rand object convenient for
 * quickly rolling any number of n-sided dice.
 *
 * @version 1.0
 * @author Travis Veazey
 */
#ifndef DICE_H_
#define DICE_H_

#include <stdint.h>
#include "core/Rand.h"

class Dice
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
		 * Destructor does nothing.
		 */
		~Dice() { };

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
		 * This provides a shared state between all Dice objects, ensuring that
		 * each instance provides unique random results.
		 */
		static Rand _rand;
};

#endif

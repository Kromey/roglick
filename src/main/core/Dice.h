/**
 * File: Dice.h
 * Provides the declaration for the Dice object
 *
 * Version:
 *   1.0
 *
 * Author:
 *   Travis Veazey
 *
 * Date:
 *   2015-03-25
 */
#ifndef DICE_H_
#define DICE_H_

#include <stdint.h>
#include "core/Rand.h"

/**
 * Class: Dice
 *
 * A dice-rolling object.
 *
 * Dice provides a lightweight rapper around the Rand object convenient for
 * quickly rolling any number of n-sided dice.
 */
class Dice
{
	/**
	 * Group: Public
	 */
	public:
		/**
		 * Constructor: Dice
		 *
		 * Creates an instance of the Dice object representing n d-sided dice.
		 *
		 * Parameters:
		 *
		 *   n - The number of dice to roll
		 *   d - How many sides on each die
		 */
		Dice(uint32_t n = 1, uint32_t d = 6);

		/**
		 * Destructor: ~Dice
		 *
		 * Destructor does nothing.
		 */
		~Dice() { };

		/**
		 * Method: roll
		 *
		 * Rolls the n d-sided dice and returns the result
		 */
		uint32_t roll();

	/**
	 * Group: Private
	 */
	private:
		/**
		 * Variable: _n
		 *
		 * This member represents how many dice we are rolling.
		 */
		uint32_t _n;

		/**
		 * Variable: _d
		 *
		 * This member represents the number of sides on each die.
		 */
		uint32_t _d;

		/**
		 * Variable: _rand
		 *
		 * This provides a shared state between all Dice objects, ensuring that
		 * each instance provides unique random results.
		 */
		static Rand _rand;
};

#endif

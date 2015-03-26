/**
 * File: Dice.cpp
 * Provides the implementation for the Dice object
 *
 * Full method and member documentation can be found in <Dice.h>.
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
#include "core/Dice.h"
#include "core/Rand.h"

//Shared PRNG state
Rand Dice::_rand = Rand();

//Constructor
Dice::Dice(uint32_t n, uint32_t d)
{
	_n = n;
	_d = d;
}

//Roll the dice
uint32_t Dice::roll()
{
	uint32_t roll = 0;

	for(uint32_t i = 0; i < _n; i++)
	{
		roll += _rand.randInt(1, _d);
	}
	return roll;
}

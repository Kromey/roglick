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
#include <time.h>

#include "core/Dice.h"
#include "core/Rand.h"

//Start with an arbitrary seed to ensure unique sequences each run.
uint32_t Dice::_dice_seed = time(NULL);

//Constructor
//Calls the seeding Rand constructor on the parent upon initialization.
Dice::Dice(uint32_t n, uint32_t d) : Rand(_dice_seed)
{
	_n = n;
	_d = d;

	//Make sure we don't reuse a seed by picking a new, random one
	_dice_seed = rand32();
}

//Roll the dice
uint32_t Dice::roll()
{
	uint32_t roll = 0;

	for(uint32_t i = 0; i < _n; i++)
	{
		roll += randInt(1, _d);
	}
	return roll;
}

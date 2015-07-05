#ifndef INPUT_H_
#define INPUT_H_

#include "interface/Command.h"

/**
 * The Input object manages capturing and interpreting player commands.
 */
class Input
{
	public:
		/**
		 * Retrieve the player's input and translate it into a Command.
		 *
		 * Note that if the key is not recognized, it returns NOOP.
		 *
		 * @return The translated Command
		 */
		Command getInput();
};

#endif

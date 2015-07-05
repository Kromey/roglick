#ifndef INPUT_H_
#define INPUT_H_

#include "interface/Command.h"
#include "interface/KeyBinding.h"

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

	private:
		KeyBinding _keymap;
};

#endif

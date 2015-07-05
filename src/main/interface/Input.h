#ifndef INPUT_H_
#define INPUT_H_

#include "interface/Command.h"
#include "interface/KeyBinding.h"
#include "interface/XYPair.h"

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

		/**
		 * Convert a movement command into an XYPair describing the direction
		 * to be moved in. This will work for character or viewport movement.
		 *
		 * If the Command is not a direction, this will return {0,0}.
		 *
		 * @param cmd The input Command
		 *
		 * @return An XYPair describing the direction of movement
		 */
		XYPair getMoveBy(Command cmd);

	private:
		KeyBinding _keymap;
};

#endif

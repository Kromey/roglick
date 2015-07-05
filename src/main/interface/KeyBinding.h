#ifndef KEYBINDING_H_
#define KEYBINDING_H_

#include <map>

#include "interface/Command.h"

/**
 * This class handles mapping raw key codes to actual in-game commands.
 */
class KeyBinding
{
	public:
		/**
		 * Default constructor will load the default keymap.
		 */
		KeyBinding();

		/**
		 * Translate a key code into a Command.
		 *
		 * This method expects ncurses-translated key codes, which is why it is
		 * and int rather than a char.
		 *
		 * @param key The key code
		 *
		 * @return The mapped Command
		 */
		Command getCommand(int key);

		/**
		 * Load the default keymap
		 */
		void loadDefaultKeymap();

	private:
		std::map<int, Command> _keymap;
};

#endif

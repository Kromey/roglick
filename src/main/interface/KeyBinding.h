#ifndef KEYBINDING_H_
#define KEYBINDING_H_

#include <map>

#include "interface/Command.h"

class KeyBinding
{
	public:
		KeyBinding();

		Command getCommand(int key);

		void loadDefaultKeymap();

	private:
		std::map<int, Command> _keymap;
};

#endif

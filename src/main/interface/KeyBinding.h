#ifndef KEYBINDING_H_
#define KEYBINDING_H_

#include <map>

#include "interface/Command.h"

class KeyBinding
{
	public:
		KeyBinding();

		Command getCommand(int key);

	private:
		std::map<int, Command> _keymap;
};

#endif

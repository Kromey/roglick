#include <ncurses.h>

#include "interface/KeyBinding.h"

KeyBinding::KeyBinding()
{
	loadDefaultKeymap();
}

Command KeyBinding::getCommand(int key)
{
	//Ugh! Clunky signature!
	typename std::map<int, Command>::iterator it = _keymap.find(key);

	if(_keymap.end() == it)
	{
		//Got no mapped key
		return NOOP;
	} else {
		//first is the key; second is the value
		return it->second;
	}
}

void KeyBinding::loadDefaultKeymap()
{
	//Classic Rogue movement keys
	_keymap['j'] = MOVE_N;
	_keymap['l'] = MOVE_E;
	_keymap['k'] = MOVE_S;
	_keymap['j'] = MOVE_W;
	_keymap['u'] = MOVE_NE;
	_keymap['n'] = MOVE_SE;
	_keymap['b'] = MOVE_SW;
	_keymap['y'] = MOVE_NW;

	//Keypad -- sorta (doesn't work in all terminals)
	_keymap['8'] = MOVE_N;
	_keymap['6'] = MOVE_E;
	_keymap['2'] = MOVE_S;
	_keymap['4'] = MOVE_W;
	_keymap['9'] = MOVE_NE;
	_keymap['3'] = MOVE_SE;
	_keymap['1'] = MOVE_SW;
	_keymap['7'] = MOVE_NW;

	//Move the viewport
	_keymap[KEY_UP] = VIEW_UP;
	_keymap[KEY_DOWN] = VIEW_DOWN;
	_keymap[KEY_LEFT] = VIEW_LEFT;
	_keymap[KEY_RIGHT] = VIEW_RIGHT;
	_keymap['c'] = VIEW_CENTERONPC;
	_keymap['C'] = VIEW_CENTERONPC;

	//Other commands
	_keymap['p'] = CMD_PAUSE;
	_keymap['P'] = CMD_PAUSE;
	_keymap['q'] = CMD_QUIT;
	_keymap['Q'] = CMD_QUIT;
}


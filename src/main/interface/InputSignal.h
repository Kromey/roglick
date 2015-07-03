#ifndef INPUTSIGNAL_H_
#define INPUTSIGNAL_H_

/**
 * Enumerate all of our signals here.
 */
enum InputSignal
{
	NOOP,

	MOVE_N,
	MOVE_E,
	MOVE_S,
	MOVE_W,
	MOVE_NE,
	MOVE_SE,
	MOVE_SW,
	MOVE_NW,

	VIEW_UP,
	VIEW_DOWN,
	VIEW_LEFT,
	VIEW_RIGHT,
	VIEW_CENTERONPC,

	CMD_PAUSE,
	CMD_QUIT
};

#endif

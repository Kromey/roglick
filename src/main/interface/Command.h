#ifndef COMMANDS_H_
#define COMMANDS_H_

/**
 * Enumerate all of our commands here.
 */
enum Command
{
	NOOP, ///< No-op; used as the default for an unmapped/unrecognized key

	MOVE_N, ///< Move North
	MOVE_E, ///< Move East
	MOVE_S, ///< Move South
	MOVE_W, ///< Move West
	MOVE_NE, ///< Move Northeast
	MOVE_SE, ///< Move Southeast
	MOVE_SW, ///< Move Southwest
	MOVE_NW, ///< Move Northwest

	VIEW_UP, ///< Move the viewport up
	VIEW_DOWN, ///< Move the viewport down
	VIEW_LEFT, ///< Move the viewport left
	VIEW_RIGHT, ///< Move the viewport right
	VIEW_CENTERONPC, ///< Center the viewport on the PC

	CMD_PAUSE, ///< Pause ncurses
	CMD_QUIT ///< Quit the game
};

#endif

#ifndef DISPLAYWINDOW_H_
#define DISPLAYWINDOW_H_

#include <stdint.h>

/**
 * XYPair can be used to describe any x,y (or width,height) pair.
 */
typedef struct
{
	int x; ///< X coordinate or dimension
	int y; ///< Y coordinate or dimension
} XYPair;

/**
 * Utility function to turn a pair of ints into an XYPair.
 *
 * @param x
 * @param y
 *
 * @return XYPair of x and y
 */
XYPair mkXYPair(int x, int y);

/**
 * WindowGeometry describes both position and size of a Window.
 */
typedef struct
{
	XYPair pos;  ///< Position of window's top-left corner
	XYPair size; ///< Size of window on X and Y axes
} WindowGeometry;

/**
 * A Window is little more than an identifier.
 *
 * Note that using an unsigned 8-bit integer gives us only 256 Windows; that
 * should be plenty though.
 */
typedef uint8_t Window;

/**
 * Flag value to signify a size that should be automatically calculated to fill
 * the available screen space.
 */
const int AUTO_SIZE = 0xCAFEBABE;

/**
 * A Window that fills the entire screen.
 */
const WindowGeometry FULLSCREEN_WINDOW = { {0,0}, {AUTO_SIZE,AUTO_SIZE} };

/**
 * Index returned when there is no Window.
 */
const int NO_WIN = -1;

#endif

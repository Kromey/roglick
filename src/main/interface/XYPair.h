#ifndef XYPAIR_H_
#define XYPAIR_H_

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

#endif

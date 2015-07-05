#include "interface/XYPair.h"

XYPair mkXYPair(int x, int y)
{
	XYPair pair = { x, y };
	return pair;
}

XYPair operator+(XYPair lhs, XYPair rhs)
{
	XYPair sum = { lhs.x + rhs.x, lhs.y + lhs.x };
	return sum;
}

XYPair operator-(XYPair lhs, XYPair rhs)
{
	XYPair difference = { lhs.x - rhs.x, lhs.y - rhs.y };
	return difference;
}


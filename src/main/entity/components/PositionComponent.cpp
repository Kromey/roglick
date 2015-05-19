#include "entity/components/PositionComponent.h"

bool operator==(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//A position is the same if x1==x2 and y1==y2, but this is so obvious I
	//really don't know why I'm writing a comment to tell you that...
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//No reason to duplicate code, just invert the equality operator!
	return !(lhs == rhs);
}


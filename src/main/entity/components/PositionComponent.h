#ifndef POSITIONCOMPONENT_H_
#define POSITIONCOMPONENT_H_

#include "interface/XYPair.h"

/**
 * @class PositionComponent
 * Data structure for a position component.
 *
 * Merely an alias for our XYPair.
 *
 * @todo Is this really the best solution?
 */
typedef XYPair PositionComponent;

/**
 * Equality operator for PositionComponent%s.
 *
 * Figuring out if two positions are identical is useful for e.g. figuring out
 * if a given position is occupied.
 *
 * @param lhs
 * @param rhs
 *
 * @return True if lhs and rhs describe the same position
 */
bool operator==(const PositionComponent& lhs, const PositionComponent& rhs);
/**
 * Inequality operator for PositionComponent%s.
 *
 * This is the opposite of the equality operator, of course, and has similar use
 * cases.
 *
 * @param lhs
 * @param rhs
 *
 * @return True if lhs and rhs do not describe the same position
 */
bool operator!=(const PositionComponent& lhs, const PositionComponent& rhs);

#endif

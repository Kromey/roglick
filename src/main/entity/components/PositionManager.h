#ifndef POSITIONMANAGER_H_
#define POSITIONMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/LookupComponentManager.h"

/**
 * Data structure for a position component.
 */
typedef struct
{
	int x; ///< X coordinate
	int y; ///< Y coordinate
} PositionComponent;

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

/**
 * PositionManager is the ComponentManager for Position components.
 *
 * Position is exactly what it sounds like: The x,y position of an entity on the
 * screen.
 */
class PositionManager : public LookupComponentManager<PositionComponent>
{
	public:
		/**
		 * Default and NULL-equivalent PositionComponent value.
		 */
		static const PositionComponent NULL_POS;

		virtual PositionComponent getNullComponent() { return NULL_POS; };

		/**
		 * Constructor will pre-allocate some space for performance.
		 */
		PositionManager();

		/**
		 * PositionManager is the ComponentManager sub-class for Position.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Position; };

		/**
		 * Retrieve the X coordinate of the given Entity.
		 *
		 * @param e Entity to get the coordinate of.
		 *
		 * @return The Entity's x coordinate
		 */
		int getX(Entity e);
		/**
		 * Set the Entity's X coordinate.
		 *
		 * @param e The Entity
		 * @param x X coordinate to set
		 */
		void setX(Entity e, int x);

		/**
		 * Retrieve the Y coordinate of the given Entity.
		 *
		 * @param e Entity to get the coordinate of.
		 *
		 * @return The Entity's y coordinate
		 */
		int getY(Entity e);
		/**
		 * Set the Entity's Y coordinate.
		 *
		 * @param e The Entity
		 * @param y Y coordinate to set
		 */
		void setY(Entity e, int y);

		/**
		 * Check the specified position for any Entity occupying it.
		 *
		 * @param pos The position to check
		 *
		 * @return True if any Entity is occupying it.
		 */
		bool isPositionOccupied(PositionComponent pos);
		/**
		 * Check the specified x,y coordinates for any Entity occupying it.
		 *
		 * @param x
		 * @param y
		 *
		 * @return True if any Entity is occupying it.
		 */
		bool isPositionOccupied(int x, int y);

		/**
		 * Searches all PositionComponent%s looking for an Entity at pos.
		 *
		 * @param pos The position we're looking for.
		 *
		 * @return The Entity at this position.
		 */
		Entity getEntityAtPosition(PositionComponent pos);
		/**
		 * Searches all PositionComponent%s looking for an Entity at the specified x,y
		 * coordinates.
		 *
		 * @param x
		 * @param y
		 *
		 * @return The Entity at this position.
		 */
		Entity getEntityAtPosition(int x, int y);
};

#endif

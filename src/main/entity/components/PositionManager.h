#ifndef POSITIONMANAGER_H_
#define POSITIONMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/ComponentManager.h"

/**
 * Data structure for a position component.
 */
typedef struct
{
	int x;
	int y;
} PositionComponent;

class PositionManager : public ComponentManager
{
	public:
		/**
		 * Default and NULL-equivalent PositionComponent value.
		 */
		static const PositionComponent NULL_POS;

		/**
		 * Constructor will pre-allocate some space for performance.
		 */
		PositionManager();

		/**
		 * Check if the given Entity has this manager's Component.
		 *
		 * @param e The Entity to test for.
		 *
		 * @return True if the Entity has this Component.
		 */
		virtual bool entityHasComponent(Entity e);

		/**
		 * Add the Component to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 */
		virtual void addComponent(Entity e);

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e);

		/**
		 * PositionManager is the ComponentManager sub-class for Position.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Position; };

		/**
		 * Retrieve the position of the given Entity. Returns NULL_POS if
		 * the Entity does not have a PositionComponent.
		 *
		 * @param e Entity to get the position of.
		 *
		 * @return The Entity's x,y position
		 */
		PositionComponent getPosition(Entity e);
		/**
		 * Set the PositionComponent for the given Entity.
		 *
		 * @param e The Entity
		 * @param pos Position of this Entity
		 */
		void setPosition(Entity e, PositionComponent pos);

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

	private:
		std::vector<int> _entity_map;
		std::vector<PositionComponent> _positions;
};

#endif

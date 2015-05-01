#ifndef POSITIONMANAGER_H_
#define POSITIONMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/ComponentManager.h"

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
		static const PositionComponent NO_POSITION;

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
		 * Retrieve the position of the given Entity. Returns NO_POSITION if
		 * the Entity does not have a PositionComponent.
		 *
		 * @param e Entity to get the position of.
		 *
		 * @return The Entity's x,y position
		 */
		PositionComponent getPosition(Entity e);

		/**
		 * Retrieve the X coordinate of the given Entity.
		 *
		 * @param e Entity to get the coordinate of.
		 *
		 * @return The Entity's x coordinate
		 */
		int getX(Entity e);
		/**
		 * Retrieve the Y coordinate of the given Entity.
		 *
		 * @param e Entity to get the coordinate of.
		 *
		 * @return The Entity's y coordinate
		 */
		int getY(Entity e);

	private:
		std::vector<int> _entity_map;
		std::vector<PositionComponent> _positions;
};

#endif

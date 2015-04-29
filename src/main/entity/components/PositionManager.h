#ifndef POSITIONMANAGER_H_
#define POSITIONMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/ComponentManager.h"
#include "entity/components/Component.h"

class PositionComponent : public Component
{
	public:
		PositionComponent();
		PositionComponent(int x, int y);

		void setX(int x) { _x = x; };
		void setY(int y) { _y = y; };

		int getX() { return _x; };
		int getY() { return _y; };

	private:
		int _x;
		int _y;
};

class PositionManager : public ComponentManager
{
	public:
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
		 * @param c The Component to add.
		 */
		virtual void addComponent(Entity e, Component* c);

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e);

		/**
		 * Retrieve the Entity's Component.
		 *
		 * This method will return NULL if the Entity does not have
		 * this Component.
		 *
		 * @param e The Entity to get the Component for.
		 *
		 * @return The Entity's Component.
		 */
		virtual Component* getComponent(Entity e);

	private:
		std::vector<int> _entity_map;
		std::vector<PositionComponent> _positions;
};

#endif

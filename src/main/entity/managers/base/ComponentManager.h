#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "entity/Entity.h"

/**
 * Enumeration for each of our types of components
 */
enum component_t {
	Position,
	Sprite,
	Attribute,
	Skill,
	Attack
};

/**
 * Base class for all Component Managers.
 */
class ComponentManager
{
	public:
		/**
		 * Check if the given Entity has this manager's Component.
		 *
		 * @param e The Entity to test for.
		 *
		 * @return True if the Entity has this Component.
		 */
		virtual bool entityHasComponent(Entity e) = 0;

		/**
		 * Filter the provided list of Entities down to only those that have
		 * our component.
		 *
		 * @note We have to filter a list, rather than generate one, because of
		 * the "weak reference" nature of Entities: The only way to know which
		 * Entities are still valid is to query the EntityManager. This means
		 * that a ComponentManager cannot simply provide its internal list of
		 * Entities, because it has no way of knowing which ones are still
		 * valid.
		 *
		 * @param el List of Entities to filter
		 *
		 * @return A filtered copy of the original list
		 */
		virtual EntityList filterEntitiesWithComponent(const EntityList& el);

		/**
		 * Add the Component (with default values) to the Entity.
		 *
		 * @param e The Entity to add the Component to.
		 */
		virtual void addComponent(Entity e) = 0;

		/**
		 * Remove the Component from the Entity.
		 *
		 * @param e The Entity to remove it from.
		 */
		virtual void removeComponent(Entity e) = 0;

		/**
		 * Gets the type of component that this ComponentManager subclass
		 * manages.
		 *
		 * @return One of the component_t enumerations.
		 */
		virtual component_t getComponentType() = 0;

	protected:
		/**
		 * This class must be inherited, it cannot be instantiated directly.
		 *
		 * NB: We actually gain this from having pure virtual methods already,
		 * but it can't hurt to have an extra layer e.g. in case for any reason
		 * we start to implement default versions of the above.
		 */
		ComponentManager() {};
};

#endif

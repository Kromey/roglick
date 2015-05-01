#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/components/ComponentManager.h"

/**
 * Data structure for a sprite component.
 */
typedef struct
{
	char c;
	int attributes;
	int color;
} SpriteComponent;

class SpriteManager : public ComponentManager
{
	public:
		/**
		 * Default and NULL-equivalent SpriteComponent value.
		 */
		static const SpriteComponent NULL_SPRITE;

		/**
		 * Constructor will pre-allocate some space for performance.
		 */
		SpriteManager();

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
		 * SpriteManager is the ComponentManager sub-class for Sprite.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Sprite; };

		/**
		 * Retrieve the sprite of the given Entity. Returns NULL_SPRITE if
		 * the Entity does not have a SpriteComponent.
		 *
		 * @param e Entity to get the position of.
		 *
		 * @return The Entity's SpriteComponent
		 */
		SpriteComponent getSprite(Entity e);
		/**
		 * Set the SpriteComponent for the given Entity.
		 *
		 * @param e The Entity
		 * @param sprite SpriteComponent for this Entity
		 */
		void setSprite(Entity e, SpriteComponent sprite);

	private:
		std::vector<int> _entity_map;
		std::vector<SpriteComponent> _sprites;
};

#endif

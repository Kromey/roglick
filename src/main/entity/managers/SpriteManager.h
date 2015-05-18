#ifndef SPRITEMANAGER_H_
#define SPRITEMANAGER_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/managers/base/LookupComponentManager.h"

/**
 * Data structure for a sprite component.
 */
typedef struct
{
	char c; ///< The character to render for this Entity
	int attributes; ///< Any attributes (e.g. bold) to apply
	int color; ///< The color pair to use for this Entity
} SpriteComponent;

/**
 * SpriteManager is the ComponentManager for Sprite components.
 *
 * Sprites are representations of the entity on the screen; in the case of
 * Ro'glick, they are a combination of an ASCII character, one or more
 * attributes (e.g. bold), and a color pair.
 */
class SpriteManager : public LookupComponentManager<SpriteComponent>
{
	public:
		/**
		 * Default and NULL-equivalent SpriteComponent value.
		 */
		static const SpriteComponent NULL_SPRITE;

		/**
		 * Return a NULL_SPRITE SpriteComponent
		 *
		 * @return NULL_SPRITE
		 */
		virtual SpriteComponent getNullComponent() { return NULL_SPRITE; };

		/**
		 * Constructor will pre-allocate some space for performance.
		 */
		SpriteManager();

		/**
		 * SpriteManager is the ComponentManager sub-class for Sprite.
		 *
		 * @return The Position enumeration of component_t.
		 */
		virtual component_t getComponentType() { return Sprite; };

};

#endif

#include <cstddef>

#include "entity/components/SpriteManager.h"

#define MAPBUFFER 5
#define NOVAL -1

const SpriteComponent SpriteManager::NULL_SPRITE = { '\0', 0, 0 };

SpriteManager::SpriteManager()
{
}

void SpriteManager::addComponent(Entity e)
{
	//Add default SpriteComponent to our list of Components
	setSprite(e, NULL_SPRITE);
}

void SpriteManager::removeComponent(Entity e)
{
	int idx = getComponentIndex(e);

	//Set our map to reflect that this Entity no longer has a sprite
	setComponentIndex(e, NOVAL);

	//Find the largest index in our entity_map
	int max_idx;
	Entity max_e;
	getMaxComponentIndex(max_e, max_idx);

	if(max_idx != idx)
	{
		//Fill the new gap with our current last component
		_sprites[idx] = _sprites[max_idx];
		setComponentIndex(max_e, idx);

		//Now shrink our vector to fit our new size
		_sprites.resize(_sprites.size() - 1);
	}
}

SpriteComponent SpriteManager::getSprite(Entity e)
{
	if(entityHasComponent(e))
	{
		//Look up where the Entity's sprite is kept...
		int idx = getComponentIndex(e);
		//...and fetch it
		return _sprites[idx];
	} else {
		//Entity has no sprite
		return NULL_SPRITE;
	}
}

void SpriteManager::setSprite(Entity e, SpriteComponent sprite)
{
	if(entityHasComponent(e))
	{
		int idx = getComponentIndex(e);
		_sprites[idx] = sprite;
	} else {
		//Brand spankin' new SpriteComponent
		//Add this to our vector of sprites
		_sprites.push_back(sprite);

		//Make sure we have room in our Entity map
		setComponentIndex(e, _sprites.size()-1);
	}
}


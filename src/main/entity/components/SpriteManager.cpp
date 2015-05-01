#include <cstddef>

#include "entity/components/SpriteManager.h"

#define MAPBUFFER 5
#define NOVAL -1

const SpriteComponent SpriteManager::NULL_SPRITE = { '\0', 0, 0 };

SpriteManager::SpriteManager() : _entity_map(MAPBUFFER, NOVAL)
{
}

bool SpriteManager::entityHasComponent(Entity e)
{
	if(e >= _entity_map.size() || NOVAL == _entity_map[e])
	{
		return false;
	} else {
		return true;
	}
}

void SpriteManager::addComponent(Entity e)
{
	//Add default SpriteComponent to our list of Components
	setSprite(e, NULL_SPRITE);
}

void SpriteManager::removeComponent(Entity e)
{
	int idx = _entity_map[e];

	//Set our map to reflect that this Entity no longer has a sprite
	_entity_map[e] = NOVAL;

	//Find the largest index in our entity_map
	int max_idx = idx;
	Entity max_e = e;
	for(unsigned int i = 0; i < _entity_map.size(); i++)
	{
		if(_entity_map[i] > max_idx)
		{
			max_idx = _entity_map[i];
			max_e = i;
		}
	}

	if(max_idx != idx)
	{
		//Fill the new gap with our current last component
		_sprites[idx] = _sprites[max_idx];
		_entity_map[max_e] = idx;

		//Now shrink our vector to fit our new size
		_sprites.resize(_sprites.size() - 1);
	}
}

SpriteComponent SpriteManager::getSprite(Entity e)
{
	if(entityHasComponent(e))
	{
		//Look up where the Entity's sprite is kept...
		int idx = _entity_map[e];
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
		int idx = _entity_map[e];
		_sprites[idx] = sprite;
	} else {
		//Brand spankin' new SpriteComponent
		//Add this to our vector of sprites
		_sprites.push_back(sprite);

		//Make sure we have room in our Entity map
		if(_entity_map.size() <= e)
		{
			_entity_map.resize(e+MAPBUFFER, NOVAL);
		}

		//Now update our Entity map; we just added the Component to the end
		_entity_map[e] = _sprites.size()-1;
	}
}


#include <cstddef>

#include "entity/components/SpriteManager.h"

#define MAPBUFFER 5
#define NOVAL -1

const SpriteComponent SpriteManager::NULL_SPRITE = { '\0', 0, 0 };

SpriteManager::SpriteManager()
{
}


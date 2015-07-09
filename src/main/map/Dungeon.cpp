#include "map/Dungeon.h"

Dungeon::Dungeon() : _type(Cave), _current_level(0)
{
}

Dungeon::Dungeon(dungeon_t type) : _type(type), _current_level(0)
{
}


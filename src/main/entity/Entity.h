#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdint.h>
#include <set>

/**
 * @class Entity
 * Define our Entity type.
 *
 * This is kind of a "hack" of the programmer's brains; by using the naming
 * convention for objects here for what is in reality nothing more than an alias
 * for a standard scalar type, we are aiming to "trick" the devs into thinking
 * of Entities as objects.
 */
typedef uint32_t Entity;

/**
 * A NULL_ENTITY is, as the name suggests, not a valid Entity. Not unlike NULL
 * itself, it is simply an arbitrary value that can be returned when no valid
 * Entity can be.
 */
const Entity NULL_ENTITY = 0xCAFEBABE;

/**
 * @class EntityList
 * A quick and convenient type for lists specifically of @link Entity
 * Entities @endlink
 */
typedef std::set<Entity> EntityList;
/**
 * @class EntityListIt
 * Also a quick/convenient type, this time for an EntityList iterator.
 */
typedef EntityList::iterator EntityListIt;

#endif

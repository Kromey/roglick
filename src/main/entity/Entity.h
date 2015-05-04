#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdint.h>
#include <set>

/**
 * Define our Entity type.
 *
 * This is kind of a "hack" of the programmer's brains; by using the naming
 * convention for objects here for what is in reality nothing more than an alias
 * for a standard scalar type, we are aiming to "trick" the devs into thinking
 * of Entities as objects.
 */
typedef uint32_t Entity;

/**
 * A quick and convenient type for lists specifically of @link Entities
 * Entity @endlink
 */
typedef std::set<Entity> EntityList;
/**
 * Also a quick/convenient type, this time for an EntityList iterator.
 */
typedef EntityList::iterator EntityListIt;

#endif

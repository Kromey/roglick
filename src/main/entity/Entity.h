#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdint.h>

/**
 * Define our Entity type.
 *
 * This is kind of a "hack" of the programmer's brains; by using the naming
 * convention for objects here for what is in reality nothing more than an alias
 * for a standard scalar type, we are aiming to "trick" the devs into thinking
 * of Entities as objects.
 */
typedef uint32_t Entity;

#endif

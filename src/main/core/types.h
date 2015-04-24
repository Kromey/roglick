/**
 * @file types.h
 *
 * This file defines several datatypes, that objects can use.
 */
#ifndef TYPE_H_
#define TYPE_H_

/**
 * The damageable_t type represents any attribute that can be damaged, and it
 * maintains both the current (i.e. "damaged") value, as well as the maximum.
 */
typedef struct {
	int max;
	int cur;
} damageable_t;

#endif

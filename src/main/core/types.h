/**
 * @file types.h
 *
 * This file defines several datatypes that objects can use.
 */
#ifndef TYPES_H_
#define TYPES_H_

/**
 * This type is a reference to our Attribute types.
 */
enum attrtype_t {
	Str,
	Dex,
	Sta,
	Int,
	Per,
	Acu
};

/**
 * The damageable_t type represents any attribute that can be damaged, and it
 * maintains both the current (i.e. "damaged") value, as well as the maximum.
 */
typedef struct {
	/**
	 * The maximum value
	 */
	int max;
	/**
	 * The current ("damaged") value
	 */
	int cur;
} damageable_t;

#endif

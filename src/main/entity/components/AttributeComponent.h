#ifndef ATTRIBUTECOMPONENT_H_
#define ATTRIBUTECOMPONENT_H_

/**
 * Data structure to represent current/maximum values of attributes.
 */
typedef struct
{
	int cur; ///< Current value
	int max; ///< Max value
} AttributeComponent;

/**
 * Enumeration for identifying different attributes.
 */
enum attrtype_t {
	Str,
	Dex,
	Sta,
	Int,
	Per,
	Acu
};

#endif

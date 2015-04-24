#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "core/types.h"

/**
 * The Attribute class manages Actor attributes such as Strength and Dexterity,
 * and keeps track of how much damage they have accrued.
 *
 * @author Travis Veazey
 * @version 1.0
 */
class Attribute
{
	public:
		/**
		 * Default constructor, creates an attribute with the default value.
		 */
		Attribute();
		/**
		 * Create an attribute with the value specified.
		 *
		 * @param max_attribute
		 */
		Attribute(int max_attribute);

		damageable_t getAttr();
		void setAttr(damageable_t attr);

		/**
		 * Get the maximum value of the attribute.
		 *
		 * @return The attribute's max value.
		 */
		int getMaxAttr();
		/**
		 * Set the maximum value of the attribue.
		 *
		 * @param max_attribute
		 */
		void setMaxAttr(int max_attribute);

		/**
		 * Get the current value of attribute.
		 *
		 * @return The attribute's current value.
		 */
		int getCurAttr();
		/**
		 * Set the current value of the attribute.
		 *
		 * @param cur_attribute
		 */
		void setCurAttr(int cur_attribute);

	private:
		damageable_t _attr;

		/**
		 * Maximum value of the attribute.
		 */
		int _max_attribute;
		/**
		 * Current value of the attribute.
		 */
		int _cur_attribute;

		/**
		 * Default value of attributes.
		 */
		const static int DEFAULT_ATTR = 10;
};

#endif

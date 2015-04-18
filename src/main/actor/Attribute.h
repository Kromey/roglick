#ifndef ACTOR_H_
#define ACTOR_H_

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
		 * Constructor.
		 */
		Attribute();

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
		int _max_attribute;
		int _cur_attribute;
};

#endif

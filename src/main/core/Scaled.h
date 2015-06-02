#ifndef SCALED_H_
#define SCALED_H_

/**
 * A data type for accurate fractional values.
 *
 * The Scaled object uses an internal scaling factor to store the value that it
 * represents, with the objective of maintaining integer-like accuracy up to a
 * precision sufficient for our needs. It also controls the rounding and
 * truncation rules for our values to help ensure accuracy where we need it.
 */
class Scaled
{
	public:
		/**
		 * Default constructor.
		 *
		 * Initializes a Scaled object with a value of 0.
		 */
		Scaled();
		/**
		 * Integer constructor.
		 *
		 * Initializes a Scaled object with a value equal to the supplied int.
		 *
		 * @param val
		 */
		Scaled(const int val);
		/**
		 * Copy constructor.
		 *
		 * @param rhs Scaled object to copy.
		 */
		Scaled(const Scaled& rhs);

		/**
		 * Integer cast operator.
		 *
		 * @return The integer value of this Scaled object.
		 */
		operator int();

		/**
		 * Equality operator.
		 *
		 * Returns true iff the value of this object is equal to that of rhs.
		 *
		 * @param rhs The Scaled object to compare to.
		 *
		 * @return True if the two objects are equal.
		 */
		bool operator==(const Scaled& rhs);
		/**
		 * Integer equality operator.
		 *
		 * @param rhs The integer to compare to
		 *
		 * @return True iff this obejct is equal to the integer value rhs.
		 */
		bool operator==(const int rhs);

		/**
		 * Inequality operator.
		 *
		 * @param rhs The object to compare to.
		 *
		 * @return True if this object is not equal to rhs.
		 */
		bool operator!=(const Scaled& rhs);
		/**
		 * Integer inequality operator.
		 *
		 * @param rhs The integer to compare to
		 *
		 * @return True if this object is not equal to the integer value rhs.
		 */
		bool operator!=(const int rhs);

		/**
		 * Less than operator.
		 *
		 * @param rhs The object to compare to.
		 *
		 * @return True if this object is less than rhs.
		 */
		bool operator<(const Scaled& rhs);
		/**
		 * Integer less than operator.
		 *
		 * @param rhs The integer to compare to.
		 *
		 * @return True if this object is less than the integer value rhs.
		 */
		bool operator<(const int rhs);

		/**
		 * Greater than operator.
		 *
		 * @param rhs The object to compare to.
		 *
		 * @return True if this object is greater than rhs.
		 */
		bool operator>(const Scaled& rhs);
		/**
		 * Integer greater than operator.
		 *
		 * @param rhs The integer value to compare to.
		 *
		 * @return True if this object is greater than the integer value rhs.
		 */
		bool operator>(const int rhs);

		/**
		 * Addition operator
		 *
		 * @param rhs The object to add to this one.
		 *
		 * @return The sum
		 */
		Scaled operator+(const Scaled& rhs);
		/**
		 * Integer addition operator
		 *
		 * @param rhs The integer value to add to this object.
		 *
		 * @return The sum
		 */
		Scaled operator+(const int rhs);

		/**
		 * Subtraction operator
		 *
		 * @param rhs The object to subtract from this one.
		 *
		 * @return The difference
		 */
		Scaled operator-(const Scaled& rhs);
		/**
		 * Integer subtraction operator
		 *
		 * @param rhs The integer to subtract from this object.
		 *
		 * @return The difference
		 */
		Scaled operator-(const int rhs);

		/**
		 * Multiplication operator
		 *
		 * @param rhs The object to multiply this one by.
		 *
		 * @return The result
		 */
		Scaled operator*(const Scaled& rhs);
		/**
		 * Integer multiplication operator
		 *
		 * @param rhs The integer to multiply this object by.
		 *
		 * @return The result
		 */
		Scaled operator*(const int rhs);

		/**
		 * Division operator
		 *
		 * @param rhs The object to divide this one by.
		 *
		 * @return The dividend
		 */
		Scaled operator/(const Scaled& rhs);
		/**
		 * Integer division operator
		 *
		 * @param rhs The integer to divide this object by.
		 *
		 * @return The dividend
		 */
		Scaled operator/(const int rhs);

	private:
		/**
		 * Scaling factor
		 *
		 * Internally, all Scaled objects are stored as multiples of this value,
		 * the result being that we are able to obtain integer-like accuracy up
		 * to our desired precision, and can more directly control rules for
		 * rounding, truncation, etc.
		 */
		static const int SCALE_FACTOR;

		/**
		 * The value this object represents, multiplied by SCALE_FACTOR.
		 */
		int _val;
};

#endif

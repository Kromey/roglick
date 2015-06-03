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
		 * @name Constructors
		 * The various constructors for the Scaled class.
		 */
		///@{
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
		 * Double/float constructor.
		 *
		 * Initializes a Scaled object with a value equal to the supplied double.
		 *
		 * @param val
		 */
		Scaled(const double val);
		/**
		 * Copy constructor.
		 *
		 * @param rhs Scaled object to copy.
		 */
		Scaled(const Scaled& rhs);
		///@}

		/**
		 * @name Cast Operators
		 * Operators to cast a Scaled object into different types.
		 */
		///@{
		/**
		 * Integer cast operator.
		 *
		 * @return The integer value of this Scaled object.
		 */
		operator int();
		/**
		 * Float cast operator.
		 *
		 * @return The float value of this Scaled object.
		 */
		operator float();
		/**
		 * Double cast operator.
		 *
		 * @return The double value of this Scaled object.
		 */
		operator double();
		///@}

		/**
		 * @name Boolean Operators
		 * Logical operators to act on Scaled types.
		 */
		///@{
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
		 * Double equality operator.
		 *
		 * @param rhs The double to compare to.
		 *
		 * @return True if this object is equal to the double value rhs.
		 */
		bool operator==(const double rhs);

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
		 * Double inequality operator.
		 *
		 * @param rhs The double to compare to
		 *
		 * @return True if this object is not equal to the double value rhs.
		 */
		bool operator!=(const double rhs);

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
		 * Double less than operator.
		 *
		 * @param rhs The double to compare to.
		 *
		 * @return True if this object is less than the double value rhs.
		 */
		bool operator<(const double rhs);

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
		 * Double greater than operator.
		 *
		 * @param rhs The double value to compare to.
		 *
		 * @return True if this object is greater than the double value rhs.
		 */
		bool operator>(const double rhs);

		/**
		 * Less than or equal to operator.
		 *
		 * @param rhs The object to compare to.
		 *
		 * @return True if this object is less than or equal to rhs.
		 */
		bool operator<=(const Scaled& rhs);
		/**
		 * Integer less than or equal to operator.
		 *
		 * @param rhs The integer to compare to.
		 *
		 * @return True if this object is less than or equal to the integer value rhs.
		 */
		bool operator<=(const int rhs);
		/**
		 * Double less than or equal to operator.
		 *
		 * @param rhs The double to compare to.
		 *
		 * @return True if this object is less than or equal to the double value rhs.
		 */
		bool operator<=(const double rhs);

		/**
		 * Greater than or equal to operator.
		 *
		 * @param rhs The object to compare to.
		 *
		 * @return True if this object is greater than or equal to rhs.
		 */
		bool operator>=(const Scaled& rhs);
		/**
		 * Integer greater than or equal to operator.
		 *
		 * @param rhs The integer value to compare to.
		 *
		 * @return True if this object is greater than or equal to the integer value rhs.
		 */
		bool operator>=(const int rhs);
		/**
		 * Double greater than or equal to operator.
		 *
		 * @param rhs The double value to compare to.
		 *
		 * @return True if this object is greater than or equal to the double value rhs.
		 */
		bool operator>=(const double rhs);

		/**
		 * Negation operator
		 *
		 * @return The logical inverse of this object
		 */
		bool operator!();
		///@}

		/**
		 * @name Arithmetic Operators
		 * Do some math.
		 */
		///@{
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
		 * Double addition operator
		 *
		 * @param rhs The double value to add to this object.
		 *
		 * @return The sum
		 */
		Scaled operator+(const double rhs);

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
		 * Double subtraction operator
		 *
		 * @param rhs The double to subtract from this object.
		 *
		 * @return The difference
		 */
		Scaled operator-(const double rhs);

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
		 * Double multiplication operator
		 *
		 * @param rhs The double to multiply this object by.
		 *
		 * @return The result
		 */
		Scaled operator*(const double rhs);

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
		/**
		 * Double division operator
		 *
		 * @param rhs The double to divide this object by.
		 *
		 * @return The dividend
		 */
		Scaled operator/(const double rhs);
		///@}

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

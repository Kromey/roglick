#ifndef SCALED_H_
#define SCALED_H_

class Scaled
{
	public:
		Scaled();
		Scaled(const int val);
		Scaled(const Scaled& rhs);

		operator int();

		Scaled operator+(const Scaled& rhs);
		Scaled operator+(const int rhs);

		Scaled operator-(const Scaled& rhs);
		Scaled operator-(const int rhs);

		Scaled operator*(const Scaled& rhs);
		Scaled operator*(const int rhs);

		Scaled operator/(const Scaled& rhs);
		Scaled operator/(const int rhs);

	private:
		static const int SCALE_FACTOR;

		int _val;
};

#endif

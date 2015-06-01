#ifndef SCALED_H_
#define SCALED_H_

class Scaled
{
	public:
		Scaled();
		Scaled(int val);

		operator int();

		Scaled operator+(const Scaled& rhs);
		Scaled operator+(const int rhs);

		Scaled operator-(const Scaled& rhs);
		Scaled operator-(const int rhs);

	private:
		static const int SCALE_FACTOR;

		int _val;
};

#endif

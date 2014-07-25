#ifndef RAND_H_
#define RAND_H_

#include <stdint.h>

class Rand
{
	public:
		Rand(int seed = 0);
		int randbit();
	private:
		uint16_t regA;
};

#endif

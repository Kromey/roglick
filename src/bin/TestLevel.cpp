#include "map/Level.h"
#include "map/generators/DummyGenerator.h"

int main()
{
	map::DummyGenerator gen1;
	map::Level l1(40, 80, gen1);

	l1.printLevel();

	return 0;
}

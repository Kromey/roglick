#include "map/Level.h"
#include "map/generators/DummyGenerator.h"

int main()
{
	DummyGenerator gen1;
	Level l1(40, 80, gen1);

	l1.printLevel();

	return 0;
}

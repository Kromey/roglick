#include "map/Level.h"
#include "map/generators/CaveGenerator.h"

int main()
{
	CaveGenerator gen1;
	Level l1(40, 80, gen1);

	l1.printLevel();

	return 0;
}

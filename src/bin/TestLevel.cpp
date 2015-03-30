#include "map/Level.h"
#include "map/generators/BigRoomGenerator.h"

int main()
{
	BigRoomGenerator gen1;
	Level l1(40, 80, gen1);

	l1.printLevel();

	return 0;
}

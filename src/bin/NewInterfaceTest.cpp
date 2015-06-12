#include <unistd.h>

#include "display/Interface.h"

int main()
{
	Interface interface;

	WindowGeometry geo_top = { {0,0}, {AUTO_SIZE, 3} };
	WindowGeometry geo_left = { {0,3}, {20, AUTO_SIZE} };
	WindowGeometry geo_map = { {20, 3}, {AUTO_SIZE, AUTO_SIZE} };

	Window top = interface.addWindow(geo_top);
	Window left = interface.addWindow(geo_left);
	Window map = interface.addWindow(geo_map);

	XYPair msg_pos = {2,1};
	interface.add(top, msg_pos, "This is the top");
	interface.add(left, msg_pos, "This is the left");
	interface.add(map, msg_pos, "This is the map");

	interface.refresh();

	sleep(4);
}

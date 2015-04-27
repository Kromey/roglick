#include <time.h>
#include <ncurses.h>

#include "display/Screen.h"
#include "map/Level.h"
#include "map/filters/DrunkardsWalkFilter.h"

int main()
{
	Screen screen;

	int width = screen.getWidth()-2;
	int height = screen.getHeight()-2;

	//The base window
	WINDOW* base = newwin(height, width, 0, 0);
	//A "middle-tier" subwindow
	WINDOW* mid = subwin(base, height, width, 0, 0);
	//The "top-level" subwindow, what we use as the "viewport"
	WINDOW* sub = subwin(mid, height, width, 0, 0);

	//Print lines of text on our middle-tier subwindow
	wprintw(mid, "A drunkard's walk cave:");
	mvwprintw(mid, 2, 3, "This is another line on mid");
	//Generate a cave level
	Level cave(width, height);
	DrunkardsWalkFilter walk;
	walk.setSeed(time(NULL));
	walk.apply(cave);
	//Print the case level onto our base window
	for(int x = 0; x < cave.getWidth(); x++)
	{
		for(int y = 0; y < cave.getHeight(); y++)
		{
			mvwaddch(base, y+1, x, cave[x][y].getDisplay());
		}
	}
	//Add another line of text to our middle-tier window
	mvwprintw(mid, 4, 3, "Yet another line on mid");
	//Now refresh our viewport to display it all...
	wrefresh(sub);
	//...and wait for a keypress before we terminate
	getch();
	/**
	 * Unfortunately the result is that we only see whatever was printed "last"
	 * in our code above -- specifically, "This is another line on mid" is never
	 * seen because it is seemingly overwritten by the cave itself printed below
	 * it; "Yet another line on mid", however, apparently overwrites the cave
	 * level and is visible in the final result.
	 *
	 * The interwebs say that this is because subwindows are not, in fact, real
	 * subwindows, but rather subcoordinates that simply give a different
	 * coordinate system for accessing identical memory -- this is why the above
	 * doesn't work as we might expect, because even though we're writing the
	 * tiles of the level to our base window, our middle-tier and top-tier
	 * windows actually reference the same memory locations as our base window,
	 * and therefore the end result only displays whatever we wrote to those
	 * memory locations last.
	 *
	 * So much for my idea of an "overlay" window between the map and the
	 * viewport where I could have put entities! :(
	 */

	return 0;
}


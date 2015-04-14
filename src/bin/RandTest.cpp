#include <time.h>
#include <ncurses.h>

#include "display/Screen.h"
#include "core/Rand.h"

int main()
{
	Screen screen;

	int width = screen.getWidth()-2;
	int height = screen.getHeight()-2;
	char input = ' ';

	while('q' != input && 'Q' != input)
	{
		mvprintw(0, 0, "Rand Output:");
		Rand rand(time(NULL));
		for(int x = 0; x < width; x++)
		{
			for(int y = 0; y < height; y++)
			{
				if(rand.randBit())
				{
					mvaddch(y+1, x, '*');
				} else {
					mvaddch(y+1, x, '.');
				}
			}
		}
		refresh();
		input = getch();
	}
}

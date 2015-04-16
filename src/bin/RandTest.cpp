#include <time.h>
#include <ncurses.h>
#include <iostream>

#include "display/Screen.h"
#include "core/Rand.h"

int main()
{
	Rand rand(time(NULL));

	for(int i = 0; i < 10; i++)
	{
		std::cout << rand.randFloat() << std::endl;
	}

	Screen screen;

	int width = screen.getWidth()-2;
	int height = screen.getHeight()-2;
	char input = ' ';

	while('q' != input && 'Q' != input)
	{
		mvprintw(0, 0, "Rand Output:");
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

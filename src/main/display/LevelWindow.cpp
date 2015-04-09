#include <stdint.h>

#include "display/LevelWindow.h"
#include "map/Level.h"

LevelWindow::LevelWindow(Level* level, uint32_t view_width, uint32_t view_height)
	: ViewportWindow(level->getWidth(), level->getHeight(), view_width, view_height)
{
	_level = level;
}

LevelWindow::LevelWindow(Level* level, uint32_t view_width, uint32_t view_height, uint32_t view_x, uint32_t view_y)
	: ViewportWindow(level->getWidth(), level->getHeight(), view_width, view_height, view_x, view_y)
{
	_level = level;
}

void LevelWindow::refresh()
{
	//Load the current Level into our Window.
	loadLevel();
	//Now refresh the viewport.
	ViewportWindow::refresh();
}

void LevelWindow::loadLevel()
{
	for(uint32_t x = 0; x < _level->getWidth(); x++)
	{
		for(uint32_t y = 0; y < _level->getHeight(); y++)
		{
			add(x, y, _level->getTile(x, y).getDisplay());
		}
	}
}

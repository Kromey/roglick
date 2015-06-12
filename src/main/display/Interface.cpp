#include <ncurses.h>

#include "display/Interface.h"

Interface::Interface() : _next_window(0)
{
	//Initialized the screen
	initscr();
	//Start with a clean slate
	clear();
	//Don't echo entered characters on the screen
	noecho();
	//Enable getting function keys
	keypad(stdscr, true);

	//Hide the cursor
	curs_set(false);

	//And finally start everything up
	refresh();
}

Interface::~Interface()
{
	endwin();
}

Window Interface::addWindow(WindowGeometry geometry)
{
	//Just a basic window, no need to do anything fancy here
	return createWindow(geometry);
}

void Interface::add(Window win, XYPair pos, char c)
{
	WindowMeta win_m = getWindowMeta(win);

	if(NULL == win_m.win)
	{
		//This Window doesn't exist
		return;
	}

	XYPair size = calculateSize(win_m.geometry);

	if(pos.x < size.x && pos.y < size.y)
	{
		mvwaddch((WINDOW*)win_m.win, pos.y, pos.x, c);
	}
}

void Interface::add(Window win, XYPair pos, std::string str)
{
	WindowMeta win_m = getWindowMeta(win);

	if(NULL == win_m.win)
	{
		//This Window doesn't exist
		return;
	}

	XYPair size = calculateSize(win_m.geometry);

	if(pos.x < size.x && pos.y < size.y)
	{
		mvwprintw((WINDOW*)win_m.win, pos.y, pos.x, str.c_str());
	}
}

void Interface::refresh()
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(_windows[i].visible)
		{
			wrefresh((WINDOW*)_windows[i].win);
		}
	}
}

XYPair Interface::getScreenSize()
{
	XYPair screen;
	getmaxyx(stdscr, screen.y, screen.x);

	return screen;
}

void Interface::pause()
{
	//Save current tty modes
	def_prog_mode();
	//End ncurses mode
	endwin();
}

void Interface::resume()
{
	//Return to previous mode
	reset_prog_mode();
	//Refresh the screen to restore contents
	refresh();
}

XYPair Interface::calculateSize(WindowGeometry geometry)
{
	XYPair size = geometry.size;

	XYPair screen = getScreenSize();

	if(size.x == AUTO_SIZE || screen.x < size.x + geometry.pos.x)
	{
		//Fit the Window to the screen's width
		size.x = screen.x - geometry.pos.x;
	}
	if(size.y == AUTO_SIZE || screen.y < size.y + geometry.pos.y)
	{
		//Fit the Window to the screen's height
		size.y = screen.y - geometry.pos.y;
	}

	return size;
}

Window Interface::createWindow(WindowGeometry geometry)
{
	WindowMeta meta;

	meta.id = _next_window++; //Post-increment returns the "old" value first
	meta.geometry = geometry;
	meta.visible = true;

	XYPair size = calculateSize(geometry);

	meta.win = newwin(size.y, size.x, geometry.pos.y, geometry.pos.x);
	//Create sub-windows thusly:
	//meta.win = subwin(_super_win->_win, _height, _width, _y, _x);

	//Now store the window on our "stack"
	_windows.push_back(meta);

	return meta.id;
}

Interface::WindowMeta Interface::getWindowMeta(Window win)
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(_windows[i].id == win)
		{
			return _windows[i];
		}
	}

	WindowMeta meta = { NULL, win, FULLSCREEN_WINDOW, false };
	return meta;
}


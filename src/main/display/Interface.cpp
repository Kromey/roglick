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
	WindowMeta window = newWindowMeta(geometry);
	createWindow(window);

	//Now store the window on our "stack"
	_windows.push_back(window);

	return window.id;
}

Window Interface::addWindow(WindowGeometry window, WindowGeometry viewport)
{
	//First create the parent Window
	WindowMeta parent = newWindowMeta(window);
	parent.visible = false;
	createWindow(parent);

	//Now store the window on our "stack"
	_windows.push_back(parent);

	//Now create the subwindow/viewport
	WindowMeta view = newWindowMeta(viewport);
	view.parent = parent.id;
	createWindow(view);

	//Now store the window on our "stack"
	_windows.push_back(view);

	return view.id;
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
		if(_windows[i].visible && NULL != _windows[i].win)
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

	if(size.x == AUTO_SIZE)
	{
		//Fit the Window to the screen's width
		size.x = screen.x - geometry.pos.x;
	}
	if(size.y == AUTO_SIZE)
	{
		//Fit the Window to the screen's height
		size.y = screen.y - geometry.pos.y;
	}

	return size;
}

Interface::WindowMeta Interface::newWindowMeta(WindowGeometry geometry)
{
	WindowMeta meta;

	meta.id = _next_window++; //Post-increment returns the "old" value first
	meta.parent = meta.id; //Not making a viewport here
	meta.geometry = geometry;
	meta.visible = true;

	return meta;
}

void Interface::createWindow(Interface::WindowMeta& window)
{
	XYPair size = calculateSize(window.geometry);

	if(window.parent == window.id)
	{
		window.win = newwin(size.y, size.x, window.geometry.pos.y, window.geometry.pos.x);
	} else {
		//Creating a sub-window; first get our parent
		WindowMeta parent = getWindowMeta(window.parent);
		window.win = subwin((WINDOW*)parent.win, size.y, size.x,
			window.geometry.pos.y, window.geometry.pos.x);
	}
}

int Interface::getWindowIndex(Window win)
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(_windows[i].id == win)
		{
			return i;
		}
	}

	return NO_WIN;
}

Interface::WindowMeta Interface::getWindowMeta(Window win)
{
	int idx = getWindowIndex(win);

	if(0 <= idx)
	{
		return _windows[idx];
	} else {
		//Didn't find the Window, return a dummy one instead.
		WindowMeta meta = { NULL, win, FULLSCREEN_WINDOW, false, win };
		return meta;
	}
}


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

	//Now store our initial screen size
	_current_screen_size = getScreenSize();

	//And finally start everything up
	refresh();
}

Interface::~Interface()
{
	//Close all Windows
	closeWindows();

	endwin();
}

Window Interface::addWindow(WindowGeometry geometry)
{
	//Just a basic window, no need to do anything fancy here
	WindowMeta window = newWindowMeta(geometry);
	openWindow(window);

	//Now store the window on our "stack"
	_windows.push_back(window);

	return window.id;
}

Window Interface::addWindow(WindowGeometry window, WindowGeometry viewport)
{
	//First create the parent Window
	WindowMeta parent = newWindowMeta(window);
	parent.visible = false;
	openWindow(parent);

	//Now store the window on our "stack"
	_windows.push_back(parent);

	//Now create the subwindow/viewport
	WindowMeta view = newWindowMeta(viewport);
	view.parent = parent.id;
	openWindow(view);

	//Now store the window on our "stack"
	_windows.push_back(view);

	return view.id;
}

Window Interface::addWindow(Level& level, WindowGeometry viewport)
{
	//First create the geometry for our parent Window
	WindowGeometry window = { {0,0}, {level.getWidth(), level.getHeight()} };
	//Now add our Windows
	Window view_win = addWindow(window, viewport);

	//Now we need to update the parent with its Level
	WindowMeta view_meta = getWindowMeta(view_win);
	int level_idx = getWindowIndex(view_meta.parent);
	_windows[level_idx].level = &level;

	return view_win;
}

Window Interface::getWindowParent(Window win)
{
	return getWindowMeta(win).parent;
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
	//Check screen size against what we've last drawn for
	XYPair screen = getScreenSize();
	if(screen.x != _current_screen_size.x || screen.y != _current_screen_size.y)
	{
		//Screen size has changed, redraw our Windows
		redraw();
		//And update our screen size
		_current_screen_size = screen;
	}

	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(_windows[i].visible && NULL != _windows[i].win)
		{
			wrefresh((WINDOW*)_windows[i].win);
		}
	}
}

void Interface::redraw()
{
	//Close and re-open all non-sub-Windows
	//Need to make sure we've taken care of all the parents first, so we skip
	//sub-Windows for now
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].win && _windows[i].parent == _windows[i].id)
		{
			//This is not a sub-window, close and re-open it
			closeWindow(_windows[i].id);
			openWindow(_windows[i]);
		}
	}

	//Now we have to go back through and do the same for child Windows
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].win && _windows[i].parent != _windows[i].id)
		{
			//This is a sub-window, close and re-open it
			closeWindow(_windows[i].id);
			openWindow(_windows[i]);
		}
	}
}

void Interface::loadLevel(Window win)
{
	WindowMeta window = getWindowMeta(win);

	if(NULL != window.level)
	{
		XYPair tile_pos = { 0, 0 };
		for(int x = 0; x < window.level->getWidth(); x++)
		{
			tile_pos.x = x;
			for(int y = 0; y < window.level->getHeight(); y++)
			{
				tile_pos.y = y;
				add(win, tile_pos, window.level->getTile(x, y).getDisplay());
			}
		}
	} else if(window.parent != window.id) {
		loadLevel(window.parent);
	}
}

void Interface::loadLevels()
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].level)
		{
			loadLevel(_windows[i].id);
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

void Interface::openWindow(Interface::WindowMeta& window)
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

void Interface::closeWindow(Window win)
{
	int win_idx = getWindowIndex(win);

	if(NO_WIN == win_idx)
	{
		//No Window to close
		return;
	}

	if(_windows[win_idx].id != _windows[win_idx].parent)
	{
		//Close parent Window first
		closeWindow(_windows[win_idx].parent);
	}

	if(NULL != _windows[win_idx].win)
	{
		//Close this Window
		delwin((WINDOW*)_windows[win_idx].win);
		_windows[win_idx].win = NULL;
	}
}

void Interface::closeWindows()
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		closeWindow(_windows[i].id);
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
		WindowMeta meta = { NULL, win, FULLSCREEN_WINDOW, false, win, NULL };
		return meta;
	}
}


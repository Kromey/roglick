#include <algorithm>
#include <ncurses.h>

#include "interface/Display.h"

const Display::WindowMeta Display::NULL_WINMETA = {
	NULL,
	0,
	FULLSCREEN_WINDOW,
	false,
	0,
	{0,0},
	NULL
};

Display::Display() : _next_window(0)
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

	//Refresh stdscr to clear its "dirty" state
	wrefresh(stdscr);
}

Display::~Display()
{
	//Close all Windows
	closeWindows();

	endwin();
}

Window Display::addWindow(WindowGeometry geometry)
{
	//Just a basic window, no need to do anything fancy here
	WindowMeta window = newWindowMeta(geometry);
	openWindow(window);

	//Now store the window on our "stack"
	_windows.push_back(window);

	return window.id;
}

Window Display::addWindow(WindowGeometry window, WindowGeometry viewport)
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

Window Display::addWindow(Level& level, WindowGeometry viewport)
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

Window Display::getWindowParent(Window win)
{
	return getWindowMeta(win).parent;
}

void Display::add(Window win, XYPair pos, char c)
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

void Display::add(Window win, XYPair pos, std::string str)
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

void Display::refresh()
{
	//Check screen size against what we've last drawn for
	XYPair screen = getScreenSize();
	if(screen.x != _current_screen_size.x || screen.y != _current_screen_size.y)
	{
		//Screen size has changed, resize our Windows
		resizeWindows();
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

void Display::resizeWindows()
{
	//Resize all non-sub-Windows
	//Need to make sure we've taken care of all the parents first, so we skip
	//sub-Windows for now
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].win && _windows[i].parent == _windows[i].id)
		{
			//This is not a sub-window, resize it
			resizeWindow(_windows[i]);
		}
	}

	//Now we have to go back through and do the same for child Windows
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].win && _windows[i].parent != _windows[i].id)
		{
			//This is a sub-window, resize it
			resizeWindow(_windows[i]);
		}
	}

	//Reload any Levels that may have been truncated by the resize
	loadLevels();
}

void Display::loadLevel(Window win)
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

void Display::loadLevels()
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		if(NULL != _windows[i].level)
		{
			loadLevel(_windows[i].id);
		}
	}
}

XYPair Display::getScreenSize()
{
	XYPair screen;
	getmaxyx(stdscr, screen.y, screen.x);

	return screen;
}

XYPair Display::getWindowSize(Window win)
{
	WindowMeta wmeta = getWindowMeta(win);

	return calculateSize(wmeta.geometry);
}

void Display::moveTo(Window win, XYPair pos)
{
	//Fetch the viewport's meta
	WindowMeta view_meta = getWindowMeta(win);

	//If we're not a viewport, don't bother continuing
	if(view_meta.id == view_meta.parent)
	{
		return;
	}

	//Get the parent's meta now
	WindowMeta parent_meta = getWindowMeta(view_meta.parent);

	//Get both our and our parent's sizes
	XYPair view_size = getWindowSize(win);
	XYPair parent_size = getWindowSize(view_meta.parent);

	//Make sure our viewport won't leave our Window's boundaries.
	int x = std::min(pos.x, parent_size.x - view_size.x);
	int y = std::min(pos.y, parent_size.y - view_size.y);
	//And don't let the viewport go into negative space either
	x = std::max(0, x);
	y = std::max(0, y);

	//Store the viewport's new position
	int i = getWindowIndex(win);
	_windows[i].view_pos.x = x;
	_windows[i].view_pos.y = y;

	//Move the sub-window relative to the window.
	mvderwin((WINDOW*)parent_meta.win, y, x);
}

void Display::pause()
{
	//Save current tty modes
	def_prog_mode();
	//End ncurses mode
	endwin();
}

void Display::resume()
{
	//Return to previous mode
	reset_prog_mode();
	//Refresh the screen to restore contents
	refresh();
}

XYPair Display::calculateSize(WindowGeometry geometry)
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

Display::WindowMeta Display::newWindowMeta(WindowGeometry geometry)
{
	//Start with a blank slate
	WindowMeta meta = NULL_WINMETA;

	meta.id = _next_window++; //Post-increment returns the "old" value first
	meta.parent = meta.id; //Not making a viewport here
	meta.geometry = geometry;
	meta.visible = true;

	return meta;
}

void Display::openWindow(Display::WindowMeta& window)
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

void Display::closeWindow(Window win)
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

void Display::closeWindows()
{
	for(std::vector<WindowMeta>::size_type i = 0; i < _windows.size(); ++i)
	{
		closeWindow(_windows[i].id);
	}
}

void Display::resizeWindow(Display::WindowMeta& window)
{
	XYPair size = calculateSize(window.geometry);

	wresize((WINDOW*)window.win, size.y, size.x);
}

int Display::getWindowIndex(Window win)
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

Display::WindowMeta Display::getWindowMeta(Window win)
{
	int idx = getWindowIndex(win);

	if(0 <= idx)
	{
		return _windows[idx];
	} else {
		//Didn't find the Window, return a dummy one instead.
		WindowMeta meta = NULL_WINMETA;
		meta.id = win;
		meta.parent = win;

		return meta;
	}
}


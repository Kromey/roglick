#include <ncurses.h>
#include <sstream>
#include <algorithm>

#include "interface/Window.h"

Window::Window(int width, int height)
{
	_level = NULL;
	_super_win = NULL;

	createWindow(width, height, 0, 0);
}

Window::Window(int width, int height, int x, int y)
{
	_level = NULL;
	_super_win = NULL;

	createWindow(width, height, x, y);
}

Window::Window(Level* level)
{
	_level = level;
	_super_win = NULL;

	createWindow(level->getWidth(), level->getHeight(), 0, 0);
	loadLevel();
}

Window::Window(Window* super_win, int width, int height, int x, int y)
{
	_level = NULL;
	_super_win = super_win;

	createWindow(width, height, x, y);
}

int Window::getWidth()
{
	if(NULL == _super_win)
	{
		return _width;
	} else {
		return _super_win->getWidth();
	}
}

int Window::getHeight()
{
	if(NULL == _super_win)
	{
		return _height;
	} else {
		return _super_win->getHeight();
	}
}

int Window::getX()
{
	if(NULL == _super_win)
	{
		return _x;
	} else {
		return _super_win->getX();
	}
}

int Window::getY()
{
	if(NULL == _super_win)
	{
		return _y;
	} else {
		return _super_win->getY();
	}
}

int Window::getViewWidth()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _width;
	}
}

int Window::getViewHeight()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _height;
	}
}

int Window::getViewX()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _view_x;
	}
}

int Window::getViewY()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _view_y;
	}
}

void Window::addBorder()
{
	//Default border, using the 3-char method for ease of maintenance
	addBorder('|', '-', '+');
}

void Window::addBorder(char sides, char topbot, char corners)
{
	//Apply border to all sides and corners
	addBorder(sides, sides, topbot, topbot, corners, corners, corners, corners);
}

void Window::addBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright)
{
	//Apply the specified border to the window
	wborder(_win, left, right, top, bottom, topleft, topright, botleft, botright);
}

void Window::refresh()
{
	wrefresh(_win);
}

void Window::add(int x, int y, char c)
{
	if(x < _width && y < _height)
	{
		mvwaddch(_win, y, x, c);
	}
}

void Window::add(int x, int y, std::string str)
{
	if(x < _width && y < _height)
	{
		mvwprintw(_win, y, x, str.c_str());
	}
}

void Window::addInt(int x, int y, int num)
{
	//String stream conversion; seems rather hacky, but without mandating C++11
	//support (which is not yet widely supported) it's the best we got...
	//Performance improvements (using a static stream) based on the answer and
	//code found here: http://bit.ly/1cfvyMW
	static std::stringstream ss;
	ss.seekp(0l);
	ss.str("");
	ss << num;
	//No reason to duplicate code now that we have the string
	add(x, y, ss.str());
}

void Window::erase(int x, int y)
{
	if(x < _width && y < _height)
	{
		/// @todo Is there a "proper" erase?
		add(y, x, ' ');
	}
}

void Window::moveTo(int x, int y)
{
	//Make sure our sub-window won't leave our window's boundaries.
	x = std::min(x, getWidth() - getViewWidth());
	y = std::min(y, getHeight() - getViewHeight());

	//Store this position for later
	_view_x = x;
	_view_y = y;

	//Move the sub-window relative to the window.
	mvderwin(_win, y, x);
}

void Window::moveBy(int dx, int dy)
{
	int x = std::max(0, getViewX()+dx);
	int y = std::max(0, getViewY()+dy);

	moveTo(x, y);
}

void Window::center()
{
	//Move the sub-window
	center(getWidth()/2, getHeight()/2);
}

void Window::center(int x, int y)
{
	//Calculate where our sub-window's x,y should be when centered on this x,y
	int centered_x = std::max(0, x - getViewWidth()/2);
	int centered_y = std::max(0, y - getViewHeight()/2);

	//Move the sub-window
	moveTo(centered_x, centered_y);
}

void Window::createWindow(int width, int height, int x, int y)
{
	//Stash width and height for later reference.
	_width = width;
	_height = height;

	//Set x and y to 0.
	_x = x;
	_y = y;

	//Default sub-window position to 0,0
	_view_x = 0;
	_view_y = 0;

	if(NULL == _super_win)
	{
		//Create the window and store its pointer.
		_win = newwin(_height, _width, _y, _x);
	} else {
		//Create a subwindow
		_win = subwin(_super_win->_win, _height, _width, _y, _x);
	}
}

void Window::loadLevel()
{
	if(NULL != _level)
	{
		for(int x = 0; x < _level->getWidth(); x++)
		{
			for(int y = 0; y < _level->getHeight(); y++)
			{
				add(x, y, _level->getTile(x, y).getDisplay());
			}
		}
	} else if(NULL != _super_win) {
		_super_win->loadLevel();
	}
}


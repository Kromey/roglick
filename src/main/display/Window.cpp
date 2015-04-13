#include <ncurses.h>
#include <sstream>
#include <algorithm>

#include "display/Window.h"

Window::Window(uint32_t width, uint32_t height)
{
	_level = NULL;
	_super_win = NULL;

	createWindow(width, height, 0, 0);
}

Window::Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
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

	for(uint32_t x = 0; x < _level->getWidth(); x++)
	{
		for(uint32_t y = 0; y < _level->getHeight(); y++)
		{
			add(x, y, _level->getTile(x, y).getDisplay());
		}
	}
}

Window::Window(Window* super_win, uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	_level = NULL;
	_super_win = super_win;

	createWindow(width, height, x, y);
}

uint32_t Window::getWidth()
{
	if(NULL == _super_win)
	{
		return _width;
	} else {
		return _super_win->getWidth();
	}
}

uint32_t Window::getHeight()
{
	if(NULL == _super_win)
	{
		return _height;
	} else {
		return _super_win->getHeight();
	}
}

uint32_t Window::getX()
{
	if(NULL == _super_win)
	{
		return _x;
	} else {
		return _super_win->getX();
	}
}

uint32_t Window::getY()
{
	if(NULL == _super_win)
	{
		return _y;
	} else {
		return _super_win->getY();
	}
}

uint32_t Window::getViewWidth()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _width;
	}
}

uint32_t Window::getViewHeight()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _height;
	}
}

uint32_t Window::getViewX()
{
	if(NULL == _super_win)
	{
		return 0;
	} else {
		return _view_x;
	}
}

uint32_t Window::getViewY()
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

void Window::add(uint32_t x, uint32_t y, char c)
{
	if(x < _width && y < _height)
	{
		mvwaddch(_win, y, x, c);
	}
}

void Window::add(uint32_t x, uint32_t y, std::string str)
{
	if(x < _width && y < _height)
	{
		mvwprintw(_win, y, x, str.c_str());
	}
}

void Window::addInt(uint32_t x, uint32_t y, int num)
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

void Window::erase(uint32_t x, uint32_t y)
{
	if(x < _width && y < _height)
	{
		/// @todo Is there a "proper" erase?
		add(y, x, ' ');
	}
}

void Window::moveTo(uint32_t x, uint32_t y)
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

void Window::moveBy(int32_t dx, int32_t dy)
{
	int32_t x = std::max(0, (int32_t)getViewX()+dx);
	int32_t y = std::max(0, (int32_t)getViewY()+dy);

	moveTo(x, y);
}

void Window::center()
{
	//Move the sub-window
	center(getWidth()/2, getHeight()/2);
}

void Window::center(uint32_t x, uint32_t y)
{
	//Calculate where our sub-window's x,y should be when centered on this x,y
	uint32_t centered_x = x - getViewWidth()/2;
	uint32_t centered_y = y - getViewHeight()/2;

	//Move the sub-window
	moveTo(centered_x, centered_y);
}

void Window::createWindow(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
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


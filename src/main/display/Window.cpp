#include <ncurses.h>
#include <sstream>

#include "display/Window.h"

Window::Window(uint32_t width, uint32_t height)
{
	_level = NULL;

	createWindow(width, height, 0, 0);
}

Window::Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	_level = NULL;

	createWindow(width, height, x, y);
}

Window::Window(Level* level)
{
	_level = level;

	createWindow(level->getWidth(), level->getHeight(), 0, 0);
}

uint32_t Window::getWidth()
{
	return _width;
}

uint32_t Window::getHeight()
{
	return _height;
}

uint32_t Window::getX()
{
	return _x;
}

uint32_t Window::getY()
{
	return _y;
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

void Window::createWindow(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	//Stash width and height for later reference.
	_width = width;
	_height = height;

	//Set x and y to 0.
	_x = x;
	_y = y;

	//Create the window and store its pointer.
	_win = newwin(_height, _width, _y, _x);
}


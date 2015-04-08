#include <ncurses.h>

#include "display/Window.h"

Window::Window(uint32_t width, uint32_t height)
{
	//Stash width and height for later reference.
	_width = width;
	_height = height;

	//Set x and y to 0.
	_x = 0;
	_y = 0;

	//Create the window and store its pointer.
	_win = newwin(_height, _width, _y, _x);
}

Window::Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
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
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		mvwaddch(_win, y, x, c);
	}
}

void Window::add(uint32_t x, uint32_t y, std::string str)
{
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		mvwprintw(_win, y, x, str.c_str());
	}
}

void Window::erase(uint32_t x, uint32_t y)
{
	if(x >= 0 && x < _width && y >= 0 && y < _height)
	{
		/// @todo Is there a "proper" erase?
		add(y, x, ' ');
	}
}


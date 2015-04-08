#include <ncurses.h>
//#include <string.h>

#include "display/Window.h"

//class Window::WIN_PTR
//{
//	public:
//		WINDOW* getPtr() { return _win; }
//		void setPtr(WINDOW* win) { _win = win; }
//	private:
//		WINDOW* _win;
//};

Window::Window(uint32_t width, uint32_t height)
{
	_width = width;
	_height = height;

	_x = 0;
	_y = 0;

	//_win->setPtr(newwin(_height, _width, _y, _x));
	_win = newwin(_height, _width, _y, _x);
}

Window::Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
	_width = width;
	_height = height;

	_x = x;
	_y = y;

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

void Window::refresh()
{
	wrefresh(_win);
}

void Window::add(uint32_t x, uint32_t y, char c)
{
	/// @todo Add bounds-checking
	mvwaddch(_win, y, x, c);
}

void Window::add(uint32_t x, uint32_t y, std::string str)
{
	/// @todo Add bounds-checking
	mvwprintw(_win, y, x, str.c_str());
}

void Window::erase(uint32_t x, uint32_t y)
{
	/// @todo Is there a "proper" erase?
	add(y, x, ' ');
}


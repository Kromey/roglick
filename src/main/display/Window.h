#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdint.h>
#include <ncurses.h>

class Window
{
	public:
		Window(uint32_t width, uint32_t height);
		Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y);

		uint32_t getWidth();
		uint32_t getHeight();

		uint32_t getX();
		uint32_t getY();

		void refresh();

		void add(uint32_t x, uint32_t y, char c);

		void erase(uint32_t x, uint32_t y);
	private:
		uint32_t _width;
		uint32_t _height;

		uint32_t _x;
		uint32_t _y;

		WINDOW* _win;
};

#endif

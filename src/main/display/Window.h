#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdint.h>
#include <ncurses.h>
#include <string>

#include "map/Level.h"

/**
 * Window objects create and manage ncurses windows.
 */
class Window
{
	public:
		/**
		 * Create a new Window with the specified width and height, at 0,0.
		 *
		 * @param width
		 * @param height
		 */
		Window(uint32_t width, uint32_t height);
		/**
		 * Create a new Window with the specified width and height at x,y.
		 *
		 * @param width
		 * @param height
		 * @param x
		 * @param y
		 */
		Window(uint32_t width, uint32_t height, uint32_t x, uint32_t y);
		/**
		 * Create a new Window containing the supplied Level.
		 *
		 * @param level
		 */
		Window(Level* level);
		/**
		 * Create a subwindow of the Window object super_win, with the
		 * specified width and height, and at the specified x and y position
		 * on the screen.
		 *
		 * @param super_win
		 * @param width
		 * @param height
		 * @param x
		 * @param y
		 */
		Window(Window* super_win, uint32_t width, uint32_t height, uint32_t x, uint32_t y);

		/**
		 * Get the width of the Window.
		 *
		 * @return The width.
		 */
		uint32_t getWidth();
		/**
		 * Get the height of the Window.
		 *
		 * @return The height.
		 */
		uint32_t getHeight();

		/**
		 * Get the x position of the Window.
		 *
		 * @return The x coordinate.
		 */
		uint32_t getX();
		/**
		 * Get the y position of the Window.
		 *
		 * @return The y coordinate.
		 */
		uint32_t getY();

		/**
		 * Gets the width of the sub-window.
		 *
		 * @return Sub-window's width.
		 */
		uint32_t getViewWidth();
		/**
		 * Gets the height of the sub-window.
		 *
		 * @return Sub-window's height.
		 */
		uint32_t getViewHeight();

		/**
		 * Get the x position of the sub-window in its Window.
		 *
		 * @return Sub-window's x position in its Window.
		 */
		uint32_t getViewX();
		/**
		 * Get the y position of the sub-window in its Window.
		 *
		 * @return Sub-window's y position in its Window.
		 */
		uint32_t getViewY();

		/**
		 * Add the default border around the Window.
		 */
		void addBorder();
		/**
		 * Add the specified border characters around the Window.
		 *
		 * @param sides Left and right sides.
		 * @param topbot Top and bottom edges.
		 * @param corners The corners.
		 */
		void addBorder(char sides, char topbot, char corners);
		/**
		 * Add the specified border characters around the Window.
		 *
		 * @param left The left edge.
		 * @param right The right edge.
		 * @param top The top edge.
		 * @param bottom The bottom edge.
		 * @param topleft The top left corner.
		 * @param topright The top right corner.
		 * @param botleft The bottom left corner.
		 * @param botright The bottom right corner.
		 */
		void addBorder(char left, char right, char top, char bottom, char topleft, char topright, char botleft, char botright);

		/**
		 * Refresh the Window.
		 */
		virtual void refresh();

		/**
		 * Display the character c at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param c
		 */
		void add(uint32_t x, uint32_t y, char c);
		/**
		 * Display the string str at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param str
		 */
		void add(uint32_t x, uint32_t y, std::string str);

		/**
		 * Display the integer num at the position x,y in the Window.
		 *
		 * @param x
		 * @param y
		 * @param num
		 */
		void addInt(uint32_t x, uint32_t y, int num);

		/**
		 * Erase the character at the position x,y from the Window.
		 *
		 * @param x
		 * @param y
		 */
		void erase(uint32_t x, uint32_t y);

		/**
		 * Move the sub-window to the specified x,y coordinates within the
		 * window. This does not move the sub-window on the screen.
		 *
		 * @param x Sub-window's new x coordinate in the window.
		 * @param y Sub-window's new y coordinate in the window.
		 */
		void moveTo(uint32_t x, uint32_t y);
		/**
		 * Move the sub-window by the specified amount.
		 * This does not move the sub-window on the screen.
		 *
		 * @param dx Amount to move by on the x axis.
		 * @param dy Amount to move by on the y axis.
		 */
		void moveBy(int32_t dx, int32_t dy);

		/**
		 * Center the sub-window in the Window.
		 */
		void center();
		/**
		 * Center the sub-window on the specified coordinates.
		 *
		 * @param x X coordinate to center on.
		 * @param y Y coordinate to center on.
		 */
		void center(uint32_t x, uint32_t y);
	protected:
		/**
		 * Create a Window with the specified width, height, and on the screen
		 * at the position x,y.
		 *
		 * @param width
		 * @param height
		 * @param x
		 * @param y
		 */
		void createWindow(uint32_t width, uint32_t height, uint32_t x, uint32_t y);

		/**
		 * Window's width.
		 */
		uint32_t _width;
		/**
		 * Window's height.
		 */
		uint32_t _height;

		/**
		 * Window's x coordinate.
		 */
		uint32_t _x;
		/**
		 * Window's y coordinate.
		 */
		uint32_t _y;

		/**
		 * Sub-window's relative x coordinate within its super-window.
		 */
		uint32_t _view_x;
		/**
		 * Sub-window's relative y coordinate within its super-window.
		 */
		uint32_t _view_y;

		/**
		 * Pointer to the Window's ncurses object.
		 */
		WINDOW* _win;

		/**
		 * Pointer to this Window's super-window, if it is a sub-window.
		 */
		Window* _super_win;

		/**
		 * Pointer to the Level object we are displaying.
		 */
		Level* _level;
};

#endif

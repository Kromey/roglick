#ifndef VIEWPORTWINDOW_H_
#define VIEWPORTWINDOW_H_

#include <stdint.h>
#include <ncurses.h>
#include <string>

#include "display/Window.h"

/**
 * The ViewportWindow object creates a Window object with a movable viewport
 * looking in on it.
 */
class ViewportWindow : public Window
{
	public:
		/**
		 * Create a Window of win_width by win_height, with a viewport of
		 * view_width by view_height; the viewport will be placed on the screen
		 * at 0,0.
		 *
		 * @param win_width Width of the Window.
		 * @param win_height Height of the Window.
		 * @param view_width Width of the viewport.
		 * @param view_height Height of the viewport.
		 */
		ViewportWindow(uint32_t win_width, uint32_t win_height,
			uint32_t view_width, uint32_t view_height);
		/**
		 * Create a Window of win_width by win_height, with a viewport of
		 * view_width by view_height; the viewport will be placed on the screen
		 * at view_x, view_y
		 *
		 * @param win_width Width of the Window.
		 * @param win_height Height of the Window.
		 * @param view_width Width of the viewport.
		 * @param view_height Height of the viewport.
		 * @param view_x Viewport's x coordinate on the screen.
		 * @param view_y Viewport's y coordinate on the screen.
		 */
		ViewportWindow(uint32_t win_width, uint32_t win_height,
			uint32_t view_width, uint32_t view_height,
			uint32_t view_x, uint32_t view_y);

		/**
		 * Gets the width of the viewport.
		 *
		 * @return Viewport's width.
		 */
		uint32_t getViewWidth();
		/**
		 * Gets the height of the viewport.
		 *
		 * @return Viewport's height.
		 */
		uint32_t getViewHeight();

		/**
		 * Get the x position of the viewport on the screen.
		 *
		 * @return Viewport's x position on the screen.
		 */
		uint32_t getViewX() { return getX(); };
		/**
		 * Get the y position of the viewport on the screen.
		 *
		 * @return Viewport's y position on the screen.
		 */
		uint32_t getViewY() { return getY(); };

		/**
		 * Refresh the viewport's view.
		 */
		void refresh();

		/**
		 * Move the viewport to the specified x,y coordinates within the window.
		 * This does not move the viewport on the screen.
		 *
		 * @param x Viewport's new x coordinate in the window.
		 * @param y Viewport's new y coordinate in the window.
		 */
		void move(uint32_t x, uint32_t y);

	protected:
		/**
		 * The viewport's width and height.
		 */
		uint32_t _view_width;
		uint32_t _view_height;

		/**
		 * Reference to the ncurses viewport object.
		 */
		WINDOW* _view;
};

#endif

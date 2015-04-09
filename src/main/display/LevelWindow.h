#ifndef LEVELWINDOW_H_
#define LEVELWINDOW_H_

#include <stdint.h>

#include "display/ViewportWindow.h"
#include "map/Level.h"

/**
 * A LevelWindow is a specialized ViewportWindow specifically intended to
 * display Level objects with a movable viewport.
 *
 * @author Travis Veazey
 * @version 1.0
 */
class LevelWindow : public ViewportWindow
{
	public:
		/**
		 * This constructor places the viewport at 0,0 on the screen, and
		 * creates the underlying Window to match the size of the Level.
		 *
		 * The LevelWindow displays the referenced Level.
		 *
		 * @param level Pointer to a Level object.
		 * @param view_width Width of the viewport.
		 * @param view_height Height of the viewport.
		 */
		LevelWindow(Level* level, uint32_t view_width, uint32_t view_height);
		/**
		 * This constructor places the viewport at view_x,view_y on the screen,
		 * and creates the underlying Window to match the size of the Level.
		 *
		 * @param level Pointer to a Level object.
		 * @param view_width Width of the viewport.
		 * @param view_height Height of the viewport.
		 * @param view_x X position of the viewport on the screen.
		 * @param view_y Y position of the viewport on the screen.
		 */
		LevelWindow(Level* level, uint32_t view_width, uint32_t view_height, uint32_t view_x, uint32_t view_y);

		/**
		 * Ensure our Level is up-to-date before refreshing our view of it.
		 */
		void refresh();

	private:
		/**
		 * Pointer to the Level object we are displaying.
		 */
		Level* _level;

		/**
		 * Load the LevelWindow's Level into the underlying Window.
		 */
		void loadLevel();
};

#endif

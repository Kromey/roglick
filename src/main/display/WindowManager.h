#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <vector>

#include "display/Window.h"

/**
 * Simple class to facilitate managing multiple Window objects.
 *
 * This class is intended to hold as many Window objects as the game needs, and
 * to properly and cleanly handle overlapping Windows, hidden Windows, etc. This
 * is managed by an internal "stack" of Windows that are kept in a controlled
 * sequence that can be altered as needed, e.g. to bring a Window to the front
 * and then send it back later.
 *
 * @todo Do I need references, or is holding onto pointers sufficient?
 */
class WindowManager
{
	public:
		/**
		 * Constructor.
		 */
		WindowManager();

		/**
		 * Add a Window.
		 *
		 * Window objects are added at the "top" of the stack, meaning that
		 * the first Window added is at the "bottom" of the view and would be
		 * hidden (or partially hidden) if a Window added later overlaps it.
		 *
		 * @param win Pointer to the Window we're adding.
		 */
		void addWindow(Window* win);

		/**
		 * Retrieve pointer to the indexed Window object.
		 *
		 * Currently, the first Window given to the WindowManager via
		 * addWindow() has index 0, the second 1, and so on.
		 *
		 * @param idx Index of the Window to retrieve.
		 *
		 * @return Pointer to the referenced Window
		 */
		Window* getWindow(std::vector<Window*>::size_type idx);

		/**
		 * Refresh all visible Window objects on the stack, in proper sequence.
		 */
		void refresh();

	private:
		/**
		 * The stack of Window pointers.
		 */
		std::vector<Window*> _windows;
};

#endif

#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <vector>
#include <string>

#include "display/InterfaceWindow.h"

/**
 * The Interface object is our end-all, be-all object for managing and updating
 * the actual screen state itself.
 */
class Interface
{
	public:
		/**
		 * Constructor.
		 *
		 * Instantiating the Interface object initializes and starts the
		 * ncurses display.
		 */
		Interface();

		/**
		 * Destructor.
		 *
		 * Upon destruction of this object, the ncurses library is
		 * cleaned up and the display reset.
		 */
		~Interface();

		/**
		 * Add a new Window to the Interface as described by the supplied
		 * geometry.
		 *
		 * @param geometry
		 *
		 * @return The Window that has been created
		 */
		Window addWindow(WindowGeometry geometry);
		/**
		 * Create a Window with a viewport looking in on it.
		 *
		 * @param parent
		 * @param viewport
		 *
		 * @return The Window representing the viewport
		 */
		Window addWindow(WindowGeometry parent, WindowGeometry viewport);

		/**
		 * Display the character c at the position pos in the Window win.
		 *
		 * @param win
		 * @param pos
		 * @param c
		 */
		void add(Window win, XYPair pos, char c);
		/**
		 * Display the string str at the position pos in the Window win.
		 *
		 * @param win
		 * @param pos
		 * @param str
		 */
		void add(Window win, XYPair pos, std::string str);

		/**
		 * Refresh all (visible) Window%s.
		 */
		void refresh();

		/**
		 * Retrieve the dimensions of the screen.
		 *
		 * @return The X and Y dimensions of the screen.
		 */
		XYPair getScreenSize();

		/**
		 * Temporarily leave ncurses mode.
		 */
		void pause();
		/**
		 * Resume a paused ncurses terminal.
		 */
		void resume();

	private:
		/**
		 * A container to hold all of our meta-data describing how our Window%s
		 * should look and behave.
		 *
		 * We use a void* for win so that we can avoid "polluting" client code
		 * with all the countless global stuffs in the ncurses header.
		 */
		typedef struct
		{
			void* win; ///< Pointer to the ncurses Window.
			Window id; ///< Unique ID
			WindowGeometry geometry; ///< Geometry (position and size)
			bool visible; ///< True if the Window should be drawn
			Window parent; ///< ID of the parent Window; its own if no parent
		} WindowMeta;

		/**
		 * Calculate the size of a Window, accounting for AUTO_SIZE dimensions.
		 *
		 * @param geometry Desired geometry of the Window
		 *
		 * @return The Window's size
		 */
		XYPair calculateSize(WindowGeometry geometry);

		/**
		 * Generate meta-data for a new Window.
		 *
		 * @param geometry
		 *
		 * @return WindowMeta for a new Window
		 */
		WindowMeta newWindowMeta(WindowGeometry geometry);
		/**
		 * Create the ncurses Window described by the meta-data in window.
		 *
		 * @param window
		 */
		void createWindow(WindowMeta& window);

		int getWindowIndex(Window win);
		/**
		 * Find the specified Window and return its WindowMeta.
		 *
		 * @param win
		 *
		 * @return The WindowMeta for Window win
		 */
		WindowMeta getWindowMeta(Window win);

		/**
		 * "Ed Emberly's Big Window List"
		 */
		std::vector<WindowMeta> _windows;

		/**
		 * The ID for the next Window we create.
		 */
		Window _next_window;
};

#endif

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
		 * @param c
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
		} WindowMeta;

		/**
		 * Calculate the size of a Window, accounting for AUTO_SIZE dimensions
		 * and bounding it to the limits of the screen.
		 *
		 * @param geometry Desired geometry of the Window
		 *
		 * @return The Window's size
		 */
		XYPair calculateSize(WindowGeometry geometry);

		/**
		 * Create a new Window with the specified geometry, returning its ID.
		 *
		 * @param geometry
		 *
		 * @return Meta-data of the created Window.
		 */
		WindowMeta createWindow(WindowGeometry geometry);

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

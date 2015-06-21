#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <vector>
#include <string>

#include "display/InterfaceWindow.h"
#include "map/Level.h"

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
		 * Create a Window to contain the Level, and a viewport with the
		 * specified geometry.
		 *
		 * @param level
		 * @param viewport
		 *
		 * @return The Window representing the viewport
		 */
		Window addWindow(Level& level, WindowGeometry viewport);

		/**
		 * Retrieve the parent of the specified Window.
		 *
		 * This method will return the supplied Window if there is no parent.
		 *
		 * @param win Window to find the parent of
		 *
		 * @return The parent Window of win, or win if no parent
		 */
		Window getWindowParent(Window win);

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
		 * Resize all Window%s.
		 */
		void resizeWindows();

		/**
		 * Reload the Level displayed by this Window.
		 *
		 * Will reload the parent Level's Window if called on a viewport.
		 *
		 * @param win
		 */
		void loadLevel(Window win);
		/**
		 * Reload all Levels currently held in Windows.
		 */
		void loadLevels();

		/**
		 * Retrieve the dimensions of the screen.
		 *
		 * @return The X and Y dimensions of the screen.
		 */
		XYPair getScreenSize();

		/**
		 * Retrieve the size of the Window.
		 *
		 * @param win The Window to get the size of
		 *
		 * @return The X and Y dimensions of the Window.
		 */
		XYPair getWindowSize(Window win);

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
			Level* level; ///< Pointer to the Level contained within
		} WindowMeta;

		/**
		 * WindowMeta value when there's no Window
		 */
		static const WindowMeta NULL_WINMETA;

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
		void openWindow(WindowMeta& window);

		/**
		 * Close an opened Window and remove it entirely from our stack.
		 *
		 * @param win The Window to close
		 */
		void closeWindow(Window win);
		/**
		 * Close all open Windows.
		 */
		void closeWindows();

		/**
		 * Resize the given Window by re-calculating AUTO_SIZE dimensions for
		 * the current screen size.
		 *
		 * @param window
		 */
		void resizeWindow(WindowMeta& window);

		/**
		 * Retrieve the index of the specified Window on the stack.
		 *
		 * @param win The Window to get.
		 *
		 * @return The Window's index
		 */
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

		/**
		 * The size of the screen we've currently drawn for.
		 *
		 * This will allow us to detect the screen being resized and redraw our
		 * Windows as needed without having to watch for signals.
		 */
		XYPair _current_screen_size;
};

#endif

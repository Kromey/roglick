#ifndef INTERFACE_H_
#define INTERFACE_H_

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
		typedef struct
		{
			Window id;
			WindowGeometry geometry;
		} WindowMeta;
};

#endif

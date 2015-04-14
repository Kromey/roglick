#ifndef SCREEN_H_
#define SCREEN_H_

#include <stdint.h>

/**
 * The Screen object initializes the ncurses library.
 *
 * Destruction of the object also terminates ncurses.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class Screen
{
	public:
		/**
		 * Constructor.
		 *
		 * Instantiating the Screen object initializes and starts the
		 * ncurses display.
		 */
		Screen();

		/**
		 * Destructor.
		 *
		 * Upon destruction of this object, the ncurses library is
		 * cleaned up and the display reset.
		 */
		~Screen();

		/**
		 * Retrieve the height of the screen.
		 *
		 * @return Number of rows on the screen.
		 */
		int getHeight();

		/**
		 * Retrieve the width of the screen.
		 *
		 * @return Number of columns on the screen.
		 */
		int getWidth();

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
		 * Screen height.
		 */
		int _height;

		/**
		 * Screen width.
		 */
		int _width;
};

#endif

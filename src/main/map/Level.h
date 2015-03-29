#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdint.h>
#include "map/generators/Generator.h"

namespace map
{
	/**
	 * The level object stores and manages the maps for a level.
	 *
	 * Level objects require a generator to be supplied that will generate the
	 * map for the level.
	 *
	 * @version 1.0
	 * @author Travis Veazey
	 */
	class Level
	{
		public:
			/**
			 * Constructor.
			 *
			 * @param width Width of the level.
			 * @param height Height of the level.
			 * @param level_generator Generator to use to create the level.
			 */
			Level(uint32_t width, uint32_t height, Generator& level_generator);

			/**
			 * Destructor.
			 */
			~Level();

			/**
			 * Print the level to stdout.
			 */
			void printLevel();
		private:
			/**
			 * Initialize the level to the specified width and height.
			 */
			void initializeLevel();

			/**
			 * This two-dimensional array stores the Tile objects making up the
			 * map.
			 */
			Tile** _tiles;

			/**
			 * Width of the level.
			 */
			uint32_t _width;
			/**
			 * Height of the level.
			 */
			uint32_t _height;
	};
}

#endif

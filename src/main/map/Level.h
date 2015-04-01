#ifndef LEVEL_H_
#define LEVEL_H_

#include <stdint.h>
#include "map/generators/Generator.h"

/**
 * The Level object stores and manages the maps for a level.
 *
 * Level objects require a Generator to be supplied that will generate the
 * map for the Level.
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
		 */
		Level(uint32_t width, uint32_t height);

		/**
		 * Destructor.
		 */
		~Level();

		/**
		 * Print the level to stdout.
		 */
		void printLevel();

		/**
		 * Proxy class allows access to the Level object's individual Tile
		 * objects via two-dimensional array access.
		 */
		class Proxy
		{
			public:
				/**
				 * Constructor stores a reference to this Level object, as well
				 * as the first-level array index (the x coordinate).
				 *
				 * @param level Level object.
				 * @param x X coordinate we're accessing.
				 */
				Proxy(Level& level, uint32_t x);

				/**
				 * Retrieve the Tile object at the specified y coordinate and
				 * the x coordinate that this object is proxying.
				 *
				 * @param y The y coordinate.
				 *
				 * @return The Tile object located here.
				 */
				Tile& operator[](uint32_t y);
			private:
				/**
				 * Reference to the proxied Level object.
				 */
				Level& _level;

				/**
				 * X coordinate we're proxying the request to.
				 */
				uint32_t _x;
		};
		/**
		 * This and the corresponding Proxy object allow access to the Level
		 * object's map of Tile objects via two-dimensional array access.
		 *
		 * This operator does not permit other operations to be performed on
		 * the retrieved row except to access a particular Tile via the array
		 * access operator.
		 *
		 * @param x The x coordinate for the Tile.
		 *
		 * @return A Proxy object that allows array-style access to the y coordinate.
		 */
		Proxy operator[](uint32_t x);
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

#endif

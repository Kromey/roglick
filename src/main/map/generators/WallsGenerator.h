#ifndef WALLSGENERATOR_H_
#define WALLSGENERATOR_H_

#include <stdint.h>
#include "map/Tile.h"
#include "map/generators/Generator.h"

/**
 * The WallsGenerator simply creates a Level that is solid walls.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class WallsGenerator : public Generator
{
	public:
		/**
		 * Generate a width x height map of WallTiles.
		 *
		 * @see Generator::generateMap
		 * @param width
		 * @param height
		 * @param tiles
		 */
		void generateMap(uint32_t width, uint32_t height, Tile** tiles);
};

#endif

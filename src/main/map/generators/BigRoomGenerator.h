/**
 * The BigRoomGenerator simply creates a level that is one big room with a
 * perimeter of walls.
 *
 * @version 1.0
 * @author Travis Veazey
 */
#ifndef BIGROOMGENERATOR_H_
#define BIGROOMGENERATOR_H_

#include <stdint.h>
#include "map/Tile.h"
#include "map/generators/Generator.h"

class BigRoomGenerator : public Generator
{
	public:
		/**
		 * Generate a room that is width-2 x height-2, and surrounded by
		 * WallTiles.
		 *
		 * @see Generator::generateMap
		 * @param width
		 * @param height
		 * @param tiles
		 */
		void generateMap(uint32_t width, uint32_t height, Tile** tiles);
};

#endif

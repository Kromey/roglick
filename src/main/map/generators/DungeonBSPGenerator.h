#ifndef DUNGEONBSPGENERATOR_H_
#define DUNGEONBSPGENERATOR_H_

#include <stdint.h>
#include "map/Tile.h"
#include "map/generators/Generator.h"
#include "core/Rand.h"

/**
 * The DungeonBSPGenerator creates a random dungeon.
 *
 * The dungeon is generated using a BSP algorithm to randomly split the dungeon
 * into several areas, place rooms there, then connect "sibling" spaces together
 * with hallways until the entire dungeon is fully connected.
 *
 * http://www.roguebasin.com/index.php?title=Basic_BSP_Dungeon_generation
 *
 * @version 1.0
 * @author Travis Veazey
 */
class DungeonBSPGenerator : public Generator
{
	public:
		/**
		 * Constructor.
		 *
		 * @param splits The number of splitting operations to perform.
		 */
		DungeonBSPGenerator(uint32_t splits = 4);

		/**
		 * Generate a width x height dungeon map.
		 *
		 * @see Generator::generateMap
		 * @param width
		 * @param height
		 * @param tiles
		 */
		void generateMap(uint32_t width, uint32_t height, Tile** tiles);

		void splitTheDungeon(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t splits, Rand& rand, Tile** tiles);

	private:
		/**
		 * Number of splits for the BSP algorithm.
		 */
		uint32_t _splits;
};

#endif

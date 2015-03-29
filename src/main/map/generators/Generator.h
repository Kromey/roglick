/**
 * The Generator object defines an interface for all level generators.
 *
 * Levels are created by a Generator object, which creates the level map.
 *
 * @version 1.0
 * @author Travis Veazey
 */
#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <stdint.h>
#include "map/Tile.h"

namespace map
{
	class Generator
	{
		public:
			/**
			 * Abstract method which must be defined by each generator.
			 *
			 * @param width The width of the map to be generated.
			 * @param height The height of the map.
			 * @param tiles Array pointer to a 2D array of Tiles.
			 */
			virtual void generateMap(uint32_t width, uint32_t height, Tile** tiles) = 0;

			/**
			 * Set the generator's seed.
			 *
			 * @param seed
			 */
			void setSeed(uint32_t seed);

			/**
			 * Get the generator's seed.
			 *
			 * @return The seed.
			 */
			uint32_t getSeed();
		protected:
			/**
			 * The generator's seed.
			 */
			uint32_t _seed;
	};
}

#endif

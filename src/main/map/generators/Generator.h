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
			virtual void generateMap(uint32_t width, uint32_t height, Tile** tiles) = 0;

			void setSeed(uint32_t seed);

			uint32_t getSeed();
		protected:
			uint32_t _seed;
	};
}

#endif

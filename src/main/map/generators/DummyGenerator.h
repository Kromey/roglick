/**
 * The DummyGenerator simply creates a level that is solid walls.
 *
 * @version 1.0
 * @author Travis Veazey
 */
#ifndef DUMMYGENERATOR_H_
#define DUMMYGENERATOR_H_

#include <stdint.h>
#include "map/Tile.h"
#include "map/generators/Generator.h"

namespace map
{
	class DummyGenerator : public Generator
	{
		public:
			void generateMap(uint32_t width, uint32_t height, Tile** tiles);
	};
}

#endif

#ifndef DRUNKARDSWALKFILTER_H_
#define DRUNKARDSWALKFILTER_H_

#include <stdint.h>
#include "map/Level.h"
#include "map/Tile.h"
#include "map/filters/Filter.h"

/**
 * The DrunkardsWalkFilter applies the "drunkard's walk" -- aka "random walk" --
 * algorithm to the Level.
 *
 * By default, it applies FloorTile to the tiles it hits.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class DrunkardsWalkFilter : public Filter
{
	public:
		/**
		 * Constructor.
		 */
		DrunkardsWalkFilter();

		/**
		 * Fill a region with the same Tile type.
		 *
		 * @param level The Level to be filled.
		 */
		void apply(Level& level);

		/**
		 * Set the starting point for the walk.
		 *
		 * @param x
		 * @param y
		 */
		void setStart(uint32_t x, uint32_t y);

		/**
		 * Set whether or not the starting point for the walk should be random.
		 *
		 * @param random
		 */
		void useRandomStart(bool random);

		/**
		 * Set the Tile to apply on the walk.
		 *
		 * @param tile
		 */
		void setTile(Tile tile);

		void setTileRatio(float ratio);
	private:
		/**
		 * The starting x,y coordinates.
		 */
		uint32_t _x;
		uint32_t _y;

		/**
		 * True if we should start from a random point.
		 */
		bool _use_random_start;

		/**
		 * The Tile to apply.
		 */
		Tile _tile;

		/**
		 * The ratio of tiles to alter on the walk.
		 */
		float _ratio;
};

#endif

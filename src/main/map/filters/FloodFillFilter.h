#ifndef FLOODFILLFILTER_H_
#define FLOODFILLFILTER_H_

#include <stdint.h>
#include "map/Level.h"
#include "map/Tile.h"
#include "map/filters/Filter.h"

/**
 * The FloodFillFilter simply fills a rectangular region with one type of Tile.
 *
 * By default, it fills the entire Level with WallTiles.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class FloodFillFilter : public Filter
{
	public:
		/**
		 * Constructor.
		 */
		FloodFillFilter();

		/**
		 * Fill a region with the same Tile type.
		 *
		 * @param level The Level to be filled.
		 */
		void apply(Level& level);

		/**
		 * Set the region for the flood fill.
		 *
		 * @param x1 Starting x coordinate.
		 * @param y1 Starting y coordinate.
		 * @param x2 Ending x coordinate.
		 * @param y2 Ending y coordinate.
		 */
		void setRegion(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);

		/**
		 * Set the Tile to fill the region with.
		 *
		 * @param tile
		 */
		void setTile(Tile tile);
	private:
		/**
		 * The starting x,y coordinates.
		 */
		uint32_t _x1;
		uint32_t _y1;

		/**
		 * The ending x,y coordinates.
		 */
		uint32_t _x2;
		uint32_t _y2;

		bool _constrain_region;

		/**
		 * The Tile to fill with.
		 */
		Tile _tile;
};

#endif

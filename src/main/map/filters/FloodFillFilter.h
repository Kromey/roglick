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
		 * Set the starting point for the flood fill.
		 *
		 * @param x
		 * @param y
		 */
		void setStart(uint32_t x, uint32_t y);

		/**
		 * Set the ending point for the flood fill.
		 *
		 * @param x
		 * @param y
		 */
		void setEnd(uint32_t x, uint32_t y);

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

		/**
		 * The Tile to fill with.
		 */
		Tile _tile;
};

#endif

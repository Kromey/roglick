#ifndef BSPFILTER_H_
#define BSPFILTER_H_

#include <stdint.h>
#include "map/Level.h"
#include "map/filters/Filter.h"
#include "map/filters/FloodFillFilter.h"
#include "core/Rand.h"

/**
 * The BSPFilter applies Binary Space Partitioning to the Level.
 *
 * The BSP algorithm randomly subdivides the space into two partitions; each of
 * those partitions is then randomly subdivided into two more partitions, and
 * so on until the maximum number of iterations has been reached. Each partition
 * is then joined to its sibling, working back up until the entire space is
 * fully connected.
 *
 * http://www.roguebasin.com/index.php?title=Basic_BSP__generation
 *
 * @version 1.0
 * @author Travis Veazey
 */
class BSPFilter : public Filter
{
	public:
		/**
		 * Constructor.
		 */
		BSPFilter();

		/**
		 * Set the minimum partition size; the BSP algorithm will not partition
		 * the Level to smaller than this value.
		 *
		 * @param min_partition
		 */
		void setMinPartition(uint32_t min_partition);

		/**
		 * Apply the BSP algorithm to the Level.
		 *
		 * @param level The Level object to modify.
		 */
		void apply(Level& level);

	private:
		/**
		 * Recursively partition the level until we reach our minimum size.
		 *
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 * @param rand
		 * @param level
		 */
		void partitionLevel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Rand& rand, Level& level, uint32_t retries = 5);

		/**
		 * Create a randomly-sized room within the specified region.
		 *
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 * @param rand
		 * @param level
		 */
		void makeRoom(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, Rand& rand, Level& level);

		/**
		 * Minimum size that we will partition down to.
		 */
		uint32_t _min_partition;

		/**
		 * A FloodFillFilter for creating our rooms.
		 */
		FloodFillFilter _filler;
};

#endif

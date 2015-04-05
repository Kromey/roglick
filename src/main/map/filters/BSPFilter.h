#ifndef BSPFILTER_H_
#define BSPFILTER_H_

#include <stdint.h>
#include "map/Level.h"
#include "map/filters/Filter.h"
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
		 * Set the number of iterations of the BSP algorithm.
		 *
		 * @param partitions
		 */
		void setPartitions(uint32_t partitions);

		/**
		 * Apply the BSP algorithm to the Level.
		 *
		 * @param level The Level object to modify.
		 */
		void apply(Level& level);

	private:
		void partitionLevel(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t partitions, Rand& rand, Level& level);

		/**
		 * Number of partitions for the BSP algorithm.
		 */
		uint32_t _partitions;
};

#endif

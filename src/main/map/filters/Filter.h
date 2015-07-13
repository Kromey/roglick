#ifndef FILTER_H_
#define FILTER_H_

#include "map/Map.h"

/**
 * The Filter object defines an interface for all Filter objects.
 *
 * A Map's map is created by applying one or more Filters to it, each altering
 * the map by applying a particular algorithm.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class Filter
{
	public:
		/**
		 * Apply this filter to the supplied Map.
		 *
		 * @param map The Map to be altered.
		 */
		virtual void apply(Map& map) = 0;

		/**
		 * Set the filter's seed.
		 *
		 * @param seed
		 */
		void setSeed(int seed);

		/**
		 * Get the filter's seed.
		 *
		 * @return The seed.
		 */
		int getSeed();
	protected:
		/**
		 * The filter's seed.
		 */
		int _seed;
};

#endif

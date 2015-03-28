/**
 * The base object for map tiles.
 *
 * Tile objects define the type of map tile, contain objects on the tile, and
 * determine how they are displayed.
 *
 * @version 1.0
 * @author Travis Veazey
 */
#ifndef TILE_H_
#define TILE_H_

#include <stdint.h>

namespace map
{

	class Tile
	{
		public:
			/**
			 * Default constructor for the Tile object.
			 */
			Tile();

			/**
			 * Get the tile's transparent state; if a tile is transparent, it
			 * does not block line of sight.
			 *
			 * @return True if the tile is transparent.
			 */
			bool getTransparent();
			/**
			 * Set the tile's transparency.
			 *
			 * @see getTransparent
			 * @param isTransparent True to make it transparent.
			 */
			void setTransparent(bool isTransparent);

			/**
			 * Get the tile's passable state; if a tile is passable, characters
			 * can enter the tile, shoot through the tile, etc.
			 *
			 * @return True if the tile is passable.
			 */
			bool getPassable();
			/**
			 * Set the tile's passable state.
			 *
			 * @see getPassable
			 * @param isPassable True to make it passable.
			 */
			void setPassable(bool isPassable);

		private:
			/**
			 * The tile's flags, stored as a composite of bitmasks.
			 */
			uint32_t _flags;

			/**
			 * Retrieve the specified bit from the internal flags.
			 *
			 * @param pos The position of the bit to check.
			 *
			 * @return The state of the specified bit.
			 */
			bool getBit(uint32_t pos);

			/**
			 * Set the specified bit to the specified value.
			 *
			 * @param pos The position of the bit to set.
			 * @param value The state to set the bit to.
			 */
			void setBit(uint32_t pos, bool value);

			/**
			 * Bit positions for the various flags.
			 */
			static const uint32_t ISPASSABLE = 0;
			static const uint32_t ISTRANSPARENT = 0;
	};

}

#endif

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

namespace map
{

	class Tile
	{
		public:
			/**
			 * Default constructor for the Tile object.
			 */
			Tile();

		private:
			/**
			 * Whether or not this tile blocks line of sight.
			 */
			bool _blocksLOS;

			/**
			 * Whether or not this tile blocks movement.
			 */
			bool _blocksMovement;
	};

}

#endif

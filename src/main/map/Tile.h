/**
 * File: Tile.h
 * Provides the declaration for the Tile object
 *
 * Version:
 *   1.0
 *
 * Author:
 *   Travis Veazey
 *
 * Date:
 *   2015-03-26
 */
#ifndef TILE_H_
#define TILE_H_

/**
 * Class: Tile
 *
 * The base object for map tiles.
 *
 * Tile objects define the type of map tile, contain objects on the tile, and
 * determine how they are displayed.
 */
class Tile
{
	/**
	 * Group: Public
	 */
	public:
		/**
		 * Constructor: Tile
		 *
		 * Default constructor for the Tile object.
		 */
		Tile();

	/**
	 * Group: Private
	 */
	private:
		/**
		 * Variable: blocksLOS
		 *
		 * Whether or not this tile blocks line of sight.
		 */
		bool _blocksLOS;

		/**
		 * Variable: blocksMovement
		 *
		 * Whether or not this tile blocks movement.
		 */
		bool _blocksMovement;
};

#endif

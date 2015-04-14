#ifndef TILE_H_
#define TILE_H_

#define WallTile Tile('#', "wall", 0x00)
#define FloorTile Tile('.', "floor", 0x03)
#define ClosedDoorTile Tile('+', "wall", 0x00)
#define OpenDoorTile Tile('\'', "floor", 0x03)

#include <string>
#include <bitset>

#include "actor/Actor.h"

/**
 * The base object for map tiles.
 *
 * Tile objects define the type of map tile, contain objects on the tile, and
 * determine how they are displayed.
 *
 * @version 1.0
 * @author Travis Veazey
 */
class Tile
{
	public:
		/**
		 * Default constructor.
		 */
		Tile();
		/**
		 * Primary constructor for the Tile object.
		 */
		Tile(char display, std::string name, int flags);

		/**
		 * Equality operator.
		 *
		 * @param rhs The object to compare this one too.
		 *
		 * @return True if rhs represents the same kind of Tile.
		 */
		bool operator==(const Tile& rhs) const;

		/**
		 * Inequality operator.
		 *
		 * @param rhs The object to compare this one too.
		 *
		 * @return True if rhs represents a different kind of Tile.
		 */
		bool operator!=(const Tile& rhs) const;

		/**
		 * Get the tile's transparent state; if a tile is transparent, it
		 * does not block line of sight.
		 *
		 * @return True if the tile is transparent.
		 */
		bool getTransparent() const;
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
		bool getPassable() const;
		/**
		 * Set the tile's passable state.
		 *
		 * @see getPassable
		 * @param isPassable True to make it passable.
		 */
		void setPassable(bool isPassable);

		/**
		 * Add an Actor to this Tile.
		 *
		 * @todo Handle situations where there may already be an Actor here.
		 *
		 * @param actor Pointer to the Actor being added to this Tile.
		 */
		void addActor(Actor* actor);
		/**
		 * Remove this Tile's Actor.
		 */
		void removeActor();

		/**
		 * Get the character meant to display this Tile on screen.
		 *
		 * @return The Tile's display character.
		 */
		char getDisplay();

	private:
		/**
		 * The character to use to render this tile on the console.
		 */
		char _display;

		/**
		 * The tile's display name.
		 */
		std::string _name;

		/**
		 * The tile's flags, stored as a composite of bitmasks.
		 */
		std::bitset<8> _flags;

		/**
		 * Retrieve the specified bit from the internal flags.
		 *
		 * @param pos The position of the bit to check.
		 *
		 * @return The state of the specified bit.
		 */
		bool getBit(int pos) const;

		/**
		 * Set the specified bit to the specified value.
		 *
		 * @param pos The position of the bit to set.
		 * @param value The state to set the bit to.
		 */
		void setBit(int pos, bool value);

		Actor* _actor;

		/**
		 * Bit positions for the various flags.
		 */
		static const int ISPASSABLE = 0;
		static const int ISTRANSPARENT = 1;
};

#endif

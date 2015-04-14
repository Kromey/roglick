#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <bitset>

/**
 * Actor objects represent any and all entities in the world that can take
 * actions; Actors are not merely PCs and NPCs, but can also represent injuries,
 * poisons, and other time effects.
 *
 * @author Travis Veazey
 * @version 1.0
 */
class Actor
{
	public:
		/**
		 * Constructor for the Actor object requires the character to display
		 * for this Actor, its name, and all relevant flags.
		 *
		 * @param display
		 * @param name
		 * @param flags
		 */
		Actor(char display, std::string name, int flags);

		/**
		 * Get the character meant to display this Tile on screen.
		 *
		 * @return The Tile's display character.
		 */
		char getDisplay();

	private:
		/**
		 * The Actor's display character.
		 */
		char _display;

		/**
		 * The Actor's name.
		 */
		std::string _name;

		/**
		 * The Actor's flags.
		 */
		std::bitset<8> _flags;
};

#endif

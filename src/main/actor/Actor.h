#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <bitset>

#include "actor/Attribute.h"
#include "core/types.h"

/**
 * Actor objects represent any and all entities in the world that can take
 * actions; Actor%s are not merely PCs and NPCs, but can also represent injuries,
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

		/**
		 * Retrieve the specified Attribute.
		 *
		 * Attribute%s are referenced via the enumeration values of attrtype_t.
		 * Using this enum gives us more readable code while enforcing type
		 * safety and "free" bounds checking.
		 *
		 * @param attr An attrtype_t enumeration value.
		 *
		 * @return A reference to the requested Attribute.
		 */
		Attribute& getAttr(attrtype_t attr);

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

		/**
		 * The Actor's attributes, indexed by the integer cast of the attrtype_t
		 * enumeration.
		 */
		Attribute _attrs[6];
};

#endif

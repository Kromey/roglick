#ifndef ACTOR_H_
#define ACTOR_H_

#include <string>
#include <bitset>

#include "actor/Attribute.h"

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

		/**
		 * Retrieve the specified Attribute.
		 *
		 * Attributes are referenced by the Actor::ATTR_* constants.
		 *
		 * @param attr_id One of the Actor::ATTR_* constants
		 *
		 * @return A reference to the specified attribute.
		 */
		Attribute& getAttr(int attr_id);

		/**
		 * @name ATTR_*
		 * The ATTR_* constants provide IDs for each of the Actor's Attributes.
		 */
		//@{
		/**
		 * Strength
		 */
		static const int ATTR_STR;
		/**
		 * Dexterity
		 */
		static const int ATTR_DEX;
		/**
		 * Stamina
		 */
		static const int ATTR_STA;
		/**
		 * Intelligence
		 */
		static const int ATTR_INT;
		/**
		 * Perception
		 */
		static const int ATTR_PER;
		/**
		 * Acuity
		 */
		static const int ATTR_ACU;
		//@}

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
		 * The Actor's attributes, indexed by the ATTR_* constants.
		 */
		Attribute _attrs[6];
};

#endif

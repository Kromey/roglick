#ifndef DUNGEON_H_
#define DUNGEON_H_

#include "map/Level.h"

enum dungeon_t
{
	CaveDungeon,
	DungeonDungeon,
	CityDungeon,
	CampDungeon,
	WildernessDungeon
};

/**
 * Container/manager object for a "dungeon", which is just any set of 1 or more
 * Level%s.
 */
class Dungeon
{
	public:
		/**
		 * Default constructor will produce a Cave Dungeon.
		 */
		Dungeon();

		/**
		 * Specify the type of Dungeon to instantiate. The type governs how many
		 * Level%s and how each is generated.
		 *
		 * @param type The type to create
		 */
		Dungeon(dungeon_t type);

		/**
		 * Move to a new level of the Dungeon.
		 *
		 * This results in the Dungeon generating a new Level.
		 *
		 * @todo Should be storing seeds of previously-generated levels so they
		 * can be revisited later.
		 *
		 * @param new_level The new level to move to
		 */
		void changeDungeonLevel(int new_level);

		/**
		 * Retrieve the current Level.
		 *
		 * @return Pointer to the current Dungeon Level.
		 */
		Level* getLevel();

	private:
		/**
		 * Generate a Level for the current Dungeon level.
		 */
		void generateDungeonMap();

		/**
		 * The type for this Dungeon.
		 */
		dungeon_t _type;

		/**
		 * Current level of the Dungeon.
		 */
		int _current_level;

		/**
		 * The current Dungeon Level.
		 */
		Level* _level;
};

#endif

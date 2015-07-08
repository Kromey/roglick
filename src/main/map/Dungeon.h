#ifndef LEVEL_H_
#define LEVEL_H_

enum dungeon_t
{
	Cave,
	Dungeon,
	City,
	Camp,
	Wilderness
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

	private:
		dungeon_t _type;
};

#endif

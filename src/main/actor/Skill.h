#ifndef SKILL_H_
#define SKILL_H_

#include "core/Dice.h"

/**
 * Skill objects represent -- what else? -- characters' skills at performing
 * various tasks. The Skill object additionally handles tests against skills,
 * including determining the "degree of success" of a check.
 */
class Skill
{
	public:
		/**
		 * Create a default Skill object with no ranks.
		 */
		Skill();

		/**
		 * Retrieve the number of ranks of the Skill.
		 *
		 * NOTE: Ranks are only part of the equation in determining the level
		 * of a Skill.
		 * @see getLevel
		 *
		 * @return The number of ranks in this Skill.
		 */
		int getRanks();
		/**
		 * Set the number of ranks in this Skill.
		 *
		 * @param ranks
		 */
		void setRanks(int ranks);

		/**
		 * Calculates the level of this Skill, which takes into account all the
		 * things that go into determining such.
		 *
		 * @return The Skill's level.
		 */
		int getLevel();

		/**
		 * Get this Skill's parent Skill.
		 *
		 * @return Pointer to the Skill's parent Skill.
		 */
		Skill* getParent();
		/**
		 * Set this Skill's parent Skill.
		 *
		 * @param parent Pointer to this Skill's parent Skill.
		 */
		void setParent(Skill* parent);

		/**
		 * Test this Skill.
		 *
		 * @return True if the check passed.
		 */
		bool check();

	private:
		/**
		 * Ranks in this current Skill.
		 */
		int _ranks;

		/**
		 * The parent Skill.
		 */
		Skill* _parent;

		/**
		 * Dice object for tests against this Skill.
		 */
		Dice _dice;
};

#endif

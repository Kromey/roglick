#ifndef SKILLCOMPONENT_H_
#define SKILLCOMPONENT_H_

/**
 * Enumeration for identifying different skills.
 */
enum skill_t {
	Melee,
	Swords,
	BastardSword,
	Maces,
	SpikedMace,
	FirstAid
};

/**
 * Data structure to represent an Entity's skill.
 */
typedef struct
{
	skill_t skill; ///< The type of skill
	int ranks; ///< Current ranks in the skill
	int xp; ///< Amount of XP earned towards next rank
} SkillComponent;

#endif

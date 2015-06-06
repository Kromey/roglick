#ifndef SKILLCOMPONENT_H_
#define SKILLCOMPONENT_H_

/**
 * Data structure to represent an Entity's skill.
 */
typedef struct
{
	int ranks; ///< Current ranks in the skill
	int xp; ///< Amount of XP earned towards next rank
} SkillComponent;

/**
 * Enumeration for identifying different skills.
 */
enum skill_t {
	NOSKILL,
	Melee,
	Swords,
	BastardSword,
	Maces,
	SpikedMace,
	FirstAid
};

/**
 * This array defines our parent skill relationships.
 *
 * If a skill's parent is NOSKILL, it has no parent.
 */
const skill_t* PARENT_SKILLS = { NOSKILL, NOSKILL, Melee, Swords, Melee, Maces, NOSKILL };

#endif

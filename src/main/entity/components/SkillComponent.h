#ifndef SKILLCOMPONENT_H_
#define SKILLCOMPONENT_H_

#include <map>

#include "entity/components/AttributeComponent.h"

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
 * @todo: Dodge is actually a "meta" skill, one calculated from other attributes
 */
enum skill_t {
	None,
	Melee,
	Swords,
	BastardSword,
	Maces,
	SpikedMace,
	FirstAid,
	Dodge
};

/**
 * Data structure representing a node (skill) in the skill tree
 */
typedef struct
{
	skill_t skill; ///< The skill being defined
	skill_t parent; ///< This skill's parent skill
	attrtype_t attribute; ///< This skill's attribute
} SkillTreeNode;

/**
 * Utility function to quickly build a SkillTreeNode
 */
SkillTreeNode mkSkillTreeNode(skill_t skill, skill_t parent, attrtype_t attribute);

/**
 * Define our skill tree
 * Though it may not be the best of ideas, we make it global here so that we
 * can always get to it without having to rebuild it every time.
 */
std::map<skill_t, SkillTreeNode> buildSkillTree();
const std::map<skill_t, SkillTreeNode> SkillTree = buildSkillTree();

#endif

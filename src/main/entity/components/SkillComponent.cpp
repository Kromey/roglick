#include "entity/components/SkillComponent.h"

SkillTreeNode mkSkillTreeNode(skill_t skill, skill_t parent, attrtype_t attribute)
{
	SkillTreeNode node = {skill, parent, attribute};
	return node;
}

std::map<skill_t, SkillTreeNode> buildSkillTree()
{
	std::map<skill_t, SkillTreeNode> tree;

	tree[Melee] = mkSkillTreeNode(Melee, None, Str);
	tree[Swords] = mkSkillTreeNode(Swords, Melee, Str);
	tree[BastardSword] = mkSkillTreeNode(BastardSword, Swords, Str);
	tree[Maces] = mkSkillTreeNode(Maces, Melee, Str);
	tree[SpikedMace] = mkSkillTreeNode(SpikedMace, Maces, Str);
	tree[FirstAid] = mkSkillTreeNode(FirstAid, None, Int);
	tree[Dodge] = mkSkillTreeNode(Dodge, None, Dex);

	return tree;
}

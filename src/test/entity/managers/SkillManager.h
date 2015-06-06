#include "gtest/gtest.h"
#include "entity/managers/SkillManager.h"

TEST(SkillManagerTest, SkillManagerIsCorrectType)
{
	SkillManager sm;

	EXPECT_EQ(Skill, sm.getComponentType());
}

TEST(SkillManagerTest, EntityDoesNotHaveComponent)
{
	SkillManager sm;
	Entity e = 5;

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, AddedEntityHasComponent)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_TRUE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, RemoveComponent)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	ASSERT_TRUE(sm.entityHasComponent(e));

	sm.removeComponent(e);

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SkillManagerTest, SkillDefaultsToNULL)
{
	SkillManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_EQ(sm.getNullComponent().size(), sm.getComponent(e).size());
}

TEST(SkillManagerTest, SetSkill)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent melee = {1,2};
	SkillComponent swords = {5,4};

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);

	EXPECT_EQ(melee.ranks, sm.getComponent(e, Melee).ranks);
	EXPECT_EQ(melee.xp, sm.getComponent(e, Melee).xp);

	EXPECT_EQ(swords.ranks, sm.getComponent(e, Swords).ranks);
	EXPECT_EQ(swords.xp, sm.getComponent(e, Swords).xp);

	++melee.ranks;
	++melee.xp;
	++swords.ranks;
	++swords.xp;

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);

	EXPECT_EQ(melee.ranks, sm.getComponent(e, Melee).ranks);
	EXPECT_EQ(melee.xp, sm.getComponent(e, Melee).xp);

	EXPECT_EQ(swords.ranks, sm.getComponent(e, Swords).ranks);
	EXPECT_EQ(swords.xp, sm.getComponent(e, Swords).xp);
}


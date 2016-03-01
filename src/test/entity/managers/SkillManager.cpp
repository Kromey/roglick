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

TEST(SkillManagerTest, SkillLevel)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent melee = {3,2};
	SkillComponent swords = {6,4};
	SkillComponent bsword = {8,4};

	sm.setComponent(e, Melee, melee);
	sm.setComponent(e, Swords, swords);
	sm.setComponent(e, BastardSword, bsword);

	EXPECT_EQ(3, sm.getSkillLevel(e, Melee));
	EXPECT_EQ(7, sm.getSkillLevel(e, Swords));
	EXPECT_EQ(11, sm.getSkillLevel(e, BastardSword));
}

TEST(SkillManagerTest, AddXP)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {5,0};

	sm.setComponent(e, BastardSword, bsword);

	EXPECT_EQ(0, sm.getComponent(e, Melee).xp);
	EXPECT_EQ(0, sm.getComponent(e, Swords).xp);
	EXPECT_EQ(0, sm.getComponent(e, BastardSword).xp);

	sm.addXP(e, BastardSword, 4);

	//Remember parent skills each get half what their direct child got
	EXPECT_EQ(1, sm.getComponent(e, Melee).xp);
	EXPECT_EQ(2, sm.getComponent(e, Swords).xp);
	EXPECT_EQ(4, sm.getComponent(e, BastardSword).xp);
}

TEST(SkillManagerTest, SkillChecksFollowExpectedOdds)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {9,0};
	SkillComponent sword = {0,0};
	SkillComponent melee = {0,0};

	AttributeManager am;
	AttributeComponent strength = {10,10};

	sm.setAttributeManager(&am);

	sm.setComponent(e, BastardSword, bsword);
	sm.setComponent(e, Swords, sword);
	sm.setComponent(e, Melee, melee);
	am.setComponent(e, Str, strength);

	int iters = 3000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 9 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		SkillCheckResult attack = sm.check(e, BastardSword);
		if(attack.successful)
		{
			++successes;
		}
		//For this test we have to reset the skill to ensure it doesn't level up
		sm.setComponent(e, BastardSword, bsword);
		//Also need to reset the parents
		sm.setComponent(e, Swords, sword);
		sm.setComponent(e, Melee, melee);
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

TEST(SkillManagerTest, ModifiedSkillChecksFollowExpectedOdds)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {7,0};
	SkillComponent sword = {0,0};
	SkillComponent melee = {0,0};

	AttributeManager am;
	AttributeComponent strength = {10,10};

	sm.setAttributeManager(&am);

	sm.setComponent(e, BastardSword, bsword);
	sm.setComponent(e, Swords, sword);
	sm.setComponent(e, Melee, melee);
	am.setComponent(e, Str, strength);

	int iters = 3000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 9 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		SkillCheckResult attack = sm.check(e, BastardSword, 2);
		if(attack.successful)
		{
			++successes;
		}
		//For this test we have to reset the skill to ensure it doesn't level up
		sm.setComponent(e, BastardSword, bsword);
		//Also need to reset the parents
		sm.setComponent(e, Swords, sword);
		sm.setComponent(e, Melee, melee);
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

TEST(SkillManagerTest, SkillPenalizedByLoweredAttribute)
{
	SkillManager sm;
	Entity e = 5;
	SkillComponent bsword = {10,0};

	AttributeManager am;
	AttributeComponent strength = {15,15};

	sm.setAttributeManager(&am);

	sm.setComponent(e, BastardSword, bsword);
	am.setComponent(e, Str, strength);

	//Skill's attribute is at full, we should get the full ranks as the level
	ASSERT_EQ(10, sm.getSkillLevel(e, BastardSword));

	//Now we damage the attribute, but not quite by 20%...
	strength.cur = 13;
	am.setComponent(e, Str, strength);
	//...and we should still have full ranks for our level
	ASSERT_EQ(10, sm.getSkillLevel(e, BastardSword));

	//New we damage by 20%...
	strength.cur = 12;
	am.setComponent(e, Str, strength);
	//...and we should get penalized by 1 point
	ASSERT_EQ(9, sm.getSkillLevel(e, BastardSword));

	//Damaged by 50%...
	strength.cur = strength.max/2;
	am.setComponent(e, Str, strength);
	//...and we should get penalized by 2 point
	ASSERT_EQ(8, sm.getSkillLevel(e, BastardSword));
}


#include "gtest/gtest.h"
#include "actor/Skill.h"

TEST(SkillTest, InitialRanksZero)
{
	Skill s1;

	EXPECT_EQ(0, s1.getRanks());
}

TEST(SkillTest, NoDefaultParentSkill)
{
	Skill s1;

	EXPECT_EQ(NULL, s1.getParent());
}

TEST(SkillTest, SettableRanks)
{
	Skill s1;

	s1.setRanks(5);
	EXPECT_EQ(5, s1.getRanks());

	s1.setRanks(8);
	EXPECT_EQ(8, s1.getRanks());
}

TEST(SkillTest, LevelEqualsRanks)
{
	Skill s1;

	EXPECT_EQ(0, s1.getLevel());

	s1.setRanks(8);
	EXPECT_EQ(8, s1.getLevel());
}

TEST(SkillTest, LevelRaisedByHalfParentLevel)
{
	Skill s1, s2;

	s1.setRanks(5);
	s2.setRanks(5);

	s2.setParent(&s1);

	EXPECT_EQ(5, s1.getLevel());
	EXPECT_EQ(7, s2.getLevel());
}

TEST(SkillTest, SkillChecksFollowExpectedOdds)
{
	Skill s1;
	s1.setRanks(9);
	int iters = 1000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 13 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		if(s1.check())
		{
			++successes;
		}
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

TEST(SkillTest, ModifiedSkillChecksFollowExpectedOdds)
{
	Skill s1;
	s1.setRanks(7);
	int iters = 1000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 13 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.03);
	int lower_bound = iters * (ratio - 0.03);

	for(int i = 0; i < iters; i++)
	{
		if(s1.check(2))
		{
			++successes;
		}
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}

TEST(SkillTest, NoDefaultAttribute)
{
	Skill s1;

	EXPECT_EQ(NULL, s1.getAttribute());
}

TEST(SkillTest, SettableAttribute)
{
	Skill s1;
	Attribute a1;

	s1.setAttribute(&a1);

	EXPECT_EQ(&a1, s1.getAttribute());
}

TEST(SkillTest, SkillPenalizedByLoweredAttribute)
{
	Skill s1;
	Attribute a1(15);

	s1.setRanks(10);
	s1.setAttribute(&a1);

	//Skill's attribute is at full, we should get the full ranks as the level
	ASSERT_EQ(10, s1.getLevel());

	//Now we damage the attribute, but not quite by 20%...
	a1.setCurAttr(13);
	//...and we should still have full ranks for our level
	ASSERT_EQ(10, s1.getLevel());

	//New we damage by 20%...
	a1.setCurAttr(12);
	//...and we should get penalized by 1 point
	ASSERT_EQ(9, s1.getLevel());
}


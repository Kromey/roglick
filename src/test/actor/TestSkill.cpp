#include "gtest/gtest.h"
#include "actor/Skill.h"

TEST(SkillTest, InitialRanksZero)
{
	Skill a1;

	EXPECT_EQ(0, a1.getRanks());
}

TEST(SkillTest, NoDefaultParentSkill)
{
	Skill a1;

	EXPECT_EQ(NULL, a1.getParent());
}

TEST(SkillTest, SettableRanks)
{
	Skill a1;

	a1.setRanks(5);
	EXPECT_EQ(5, a1.getRanks());

	a1.setRanks(8);
	EXPECT_EQ(8, a1.getRanks());
}

TEST(SkillTest, LevelEqualsRanks)
{
	Skill a1;

	EXPECT_EQ(0, a1.getLevel());

	a1.setRanks(8);
	EXPECT_EQ(8, a1.getLevel());
}

TEST(SkillTest, LevelRaisedByHalfParentLevel)
{
	Skill a1, a2;

	a1.setRanks(5);
	a2.setRanks(5);

	a2.setParent(&a1);

	EXPECT_EQ(5, a1.getLevel());
	EXPECT_EQ(7, a2.getLevel());
}

TEST(SkillTest, SkillChecksFollowExpectedOdds)
{
	Skill a1;
	a1.setRanks(9);
	int iters = 1000;
	int successes = 0;
	float ratio = 0.3750;

	/**
	 * Based on calculations from AnyDice, a 3d6 roll should come in at 13 or
	 * lower 37.50% of the time. We allow some fudge because random.
	 */
	int upper_bound = iters * (ratio + 0.05);
	int lower_bound = iters * (ratio - 0.05);

	for(int i = 0; i < iters; i++)
	{
		if(a1.check())
		{
			++successes;
		}
	}

	EXPECT_GE(upper_bound, successes);
	EXPECT_LE(lower_bound, successes);
}


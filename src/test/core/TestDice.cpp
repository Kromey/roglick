#include "gtest/gtest.h"
#include "core/Dice.h"

TEST(DiceTest, RollNeverZero)
{
	Dice d1;

	int iters = 1000;
	int is_zero = 0;

	for(int i = 0; i < iters; i++)
	{
		is_zero |= (d1.roll() == 0);
	}

	EXPECT_EQ(0, is_zero);
}

TEST(DiceTest, RollNotAlwaysOne)
{
	Dice d1;
	int roll_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		roll_sum += d1.roll();
	}
	EXPECT_LT(iters, roll_sum);
}

TEST(DiceTest, RollNotAlwaysSix)
{
	Dice d1;
	int roll_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		roll_sum += d1.roll();
	}
	EXPECT_GT(iters*6, roll_sum);
}

TEST(DiceTest, DiceNotAlwaysSame)
{
	Dice d1;
	Dice d2;
	int equal = 1;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		equal &= (d1.roll() == d2.roll());
	}

	EXPECT_NE(1, equal);
}

TEST(DiceTest, MultiDiceRollNeverOne)
{
	Dice d1(2);

	int iters = 1000;
	int is_one = 0;

	for(int i = 0; i < iters; i++)
	{
		is_one |= (d1.roll() == 1);
	}

	EXPECT_EQ(0, is_one);
}

TEST(DiceTest, MultiDiceRollNotAlwaysTwo)
{
	Dice d1(2);
	int roll_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		roll_sum += d1.roll();
	}
	EXPECT_LT(iters*2, roll_sum);
}

TEST(DiceTest, DiceExpectedValue)
{
	Dice d1;
	int roll_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		roll_sum += d1.roll();
	}

	/**
	 * Expected value of a 1d6 roll is 3.5, so we test upper and lower bounds
	 * of 4 and 3, respectively, to account for randomness.
	 */
	EXPECT_LE(iters*3, roll_sum);
	EXPECT_GE(iters*4, roll_sum);
}

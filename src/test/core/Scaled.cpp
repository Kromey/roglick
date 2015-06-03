#include "gtest/gtest.h"
#include "core/Scaled.h"

TEST(ScaledTest, IntCast)
{
	Scaled s1(5);

	EXPECT_EQ(5, (int)s1);
}

TEST(ScaledTest, FloatCast)
{
	Scaled s1(1.5);

	EXPECT_FLOAT_EQ(1.5, (float)s1);
	EXPECT_FLOAT_EQ(1.5, (double)s1);
}

TEST(ScaledTest, ScaledComparisons)
{
	Scaled s1(5);
	Scaled s2(5);
	Scaled s3(3);
	Scaled s4(8);
	Scaled s5(0);

	EXPECT_TRUE(s1 == s2);
	EXPECT_FALSE(s1 == s3);

	EXPECT_FALSE(s1 != s2);
	EXPECT_TRUE(s1 != s4);

	EXPECT_FALSE(s1 < s2);
	EXPECT_FALSE(s1 < s3);
	EXPECT_TRUE(s1 < s4);

	EXPECT_FALSE(s1 > s2);
	EXPECT_TRUE(s1 > s3);
	EXPECT_FALSE(s1 > s4);

	EXPECT_TRUE(s1 <= s2);
	EXPECT_FALSE(s1 <= s3);
	EXPECT_TRUE(s1 <= s4);

	EXPECT_TRUE(s1 >= s2);
	EXPECT_TRUE(s1 >= s3);
	EXPECT_FALSE(s1 >= s4);

	EXPECT_FALSE(!s1);
	EXPECT_TRUE(!s5);
}

TEST(ScaledTest, IntComparisons)
{
	Scaled s1(5);
	Scaled s2(5);
	Scaled s3(3);
	Scaled s4(8);
	Scaled s5(0);

	EXPECT_TRUE(s1 == 5);
	EXPECT_FALSE(s1 == 4);

	EXPECT_FALSE(s1 != 5);
	EXPECT_TRUE(s1 != 4);

	EXPECT_FALSE(s1 < 5);
	EXPECT_FALSE(s1 < 3);
	EXPECT_TRUE(s1 < 8);

	EXPECT_FALSE(s1 > 5);
	EXPECT_TRUE(s1 > 3);
	EXPECT_FALSE(s1 > 8);

	EXPECT_TRUE(s1 <= 5);
	EXPECT_FALSE(s1 <= 3);
	EXPECT_TRUE(s1 <= 8);

	EXPECT_TRUE(s1 >= 5);
	EXPECT_TRUE(s1 >= 3);
	EXPECT_FALSE(s1 >= 8);
}

TEST(ScaledTest, DoubleComparisons)
{
	Scaled s1(5.6);
	Scaled s2(5.6);
	Scaled s3(3.2);
	Scaled s4(8.78);
	Scaled s5(0.2);

	EXPECT_TRUE(s1 == 5.6);
	EXPECT_FALSE(s1 == 5.5);

	EXPECT_FALSE(s1 != 5.6);
	EXPECT_TRUE(s1 != 5.5);

	EXPECT_FALSE(s1 < 5.6);
	EXPECT_FALSE(s1 < 3.2);
	EXPECT_TRUE(s1 < 8.78);

	EXPECT_FALSE(s1 > 5.6);
	EXPECT_TRUE(s1 > 3.2);
	EXPECT_FALSE(s1 > 8.78);

	EXPECT_TRUE(s1 <= 5.6);
	EXPECT_FALSE(s1 <= 3.2);
	EXPECT_TRUE(s1 <= 8.78);

	EXPECT_TRUE(s1 >= 5.6);
	EXPECT_TRUE(s1 >= 3.2);
	EXPECT_FALSE(s1 >= 8.78);
}

TEST(ScaledTest, BasicAddition)
{
	Scaled s1(2);
	Scaled s2(4);

	Scaled s3 = s1 + s2;

	EXPECT_EQ(6, (int)s3);
}

TEST(ScaledTest, BasicSubtraction)
{
	Scaled s1(6);
	Scaled s2(4);

	Scaled s3 = s1 - s2;

	EXPECT_EQ(2, (int)s3);
}

TEST(ScaledTest, AddInt)
{
	Scaled s1(2);

	Scaled s2 = s1 + 4;

	EXPECT_EQ(6, (int)s2);
}

TEST(ScaledTest, SubtractInt)
{
	Scaled s1(6);

	Scaled s2 = s1 - 4;

	EXPECT_EQ(2, (int)s2);
}

TEST(ScaledTest, AddDouble)
{
	Scaled s1(2);

	Scaled s2 = s1 + 4.5;

	EXPECT_FLOAT_EQ(6.5, (double)s2);
}

TEST(ScaledTest, SubtractDouble)
{
	Scaled s1(6);

	Scaled s2 = s1 - 4.5;

	EXPECT_FLOAT_EQ(1.5, (double)s2);
}

TEST(ScaledTest, BasicMultiplication)
{
	Scaled s1(2);
	Scaled s2(4);

	Scaled s3 = s1 * s2;

	EXPECT_EQ(8, (int)s3);
}

TEST(ScaledTest, BasicDivision)
{
	Scaled s1(6);
	Scaled s2(3);

	Scaled s3 = s1 / s2;

	EXPECT_EQ(2, (int)s3);
}

TEST(ScaledTest, MultiplyInt)
{
	Scaled s1(2);

	Scaled s2 = s1 * 4;

	EXPECT_EQ(8, (int)s2);
}

TEST(ScaledTest, DivideInt)
{
	Scaled s1(6);

	Scaled s2 = s1 / 3;

	EXPECT_EQ(2, (int)s2);
}


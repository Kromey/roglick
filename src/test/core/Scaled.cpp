#include "gtest/gtest.h"
#include "core/Scaled.h"

TEST(ScaledTest, CanRetrieveInteger)
{
	Scaled s1(5);

	EXPECT_EQ(5, (int)s1);
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


#include "gtest/gtest.h"
#include "Rand.h"

TEST(RandTest, RandNotAlwaysZero)
{
	Rand r1;
	int bit_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randbit();
	}
	EXPECT_LT(0, bit_sum);
}

TEST(RandTest, RandNotAlwaysOne)
{
	Rand r1;
	int bit_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randbit();
	}
	EXPECT_GT(iters, bit_sum);
}

TEST(RandTest, HalfBitsAreOne)
{
	Rand r1;
	int iters = 10000;
	int bit_sum = 0;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randbit();
	}

	//Give ourselves a range to allow +/- the exact mean
	int low = iters * 2 / 5;
	int high = iters * 3 / 5;

	EXPECT_LE(low, bit_sum);
	EXPECT_GE(high, bit_sum);
}

TEST(RandTest, SameSeedsAreEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 10000;
	int equal = 1;
	
	for(int i = 0; i < iters; i++)
	{
		equal &= r1.randbit() == r2.randbit();
	}

	EXPECT_EQ(1, equal);
}

TEST(RandTest, DifferentSeedsAreNotEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0x10ECAu);

	int iters = 10000;
	int equal = 1;
	
	for(int i = 0; i < iters; i++)
	{
		equal &= r1.randbit() == r2.randbit();
	}

	EXPECT_NE(1, equal);
}

TEST(RandTest, GetNBits)
{
	Rand r1;

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_GE(0xFF, r1.randn(8));
	}
}

TEST(RandTest, 8BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand8(), r2.randn(8));
	}
}

TEST(RandTest, 16BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand16(), r2.randn(16));
	}
}

TEST(RandTest, 32BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand32(), r2.randn(32));
	}
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

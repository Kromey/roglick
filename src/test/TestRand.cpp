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
	EXPECT_TRUE(bit_sum > 0);
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
	EXPECT_TRUE(bit_sum < iters);
}

//TEST(RandTest, NewAntIsAgeZero)
//{
//	Ant a1;
//	EXPECT_EQ(0, a1.getAge());
//}
//
//TEST(RandTest, AntAgesAfterUpdate)
//{
//	Ant a1;
//	a1.update();
//	EXPECT_EQ(1, a1.getAge());
//}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

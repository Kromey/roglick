#include "gtest/gtest.h"
#include "core/Rand.h"

TEST(RandTest, RandNotAlwaysZero)
{
	Rand r1;
	int bit_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randBit();
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
		bit_sum += r1.randBit();
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
		bit_sum += r1.randBit();
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
		equal &= r1.randBit() == r2.randBit();
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
		equal &= r1.randBit() == r2.randBit();
	}

	EXPECT_NE(1, equal);
}

TEST(RandTest, GetNBits)
{
	Rand r1;

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_GE(0xFF, r1.randN(8));
	}
}

TEST(RandTest, RandNNotAlwaysZero)
{
	Rand r1;
	int bit_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randN(8);
	}
	EXPECT_LT(0, bit_sum);
}

TEST(RandTest, RandNNotAlwaysMax)
{
	Rand r1;
	int bit_sum = 0;
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		bit_sum += r1.randN(8);
	}
	EXPECT_GT(iters * 0xFF, bit_sum);
}

TEST(RandTest, 8BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand8(), r2.randN(8));
	}
}

TEST(RandTest, 16BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand16(), r2.randN(16));
	}
}

TEST(RandTest, 32BitsEqual)
{
	Rand r1(0xACE01u);
	Rand r2(0xACE01u);

	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.rand32(), r2.randN(32));
	}
}

TEST(RandTest, RandIntIsInclusive)
{
	Rand r1;
	int foo[7] = {false};
	int iters = 1000;
	int result;

	for(int i = 0; i < iters; i++)
	{
		result = r1.randInt(1, 7);
		ASSERT_GE(7, result);
		ASSERT_LE(1, result);
		foo[r1.randInt(1,7)-1] = true;
	}

	for(int i = 0; i < 7; i++)
	{
		EXPECT_TRUE(foo[i]);
	}
}

TEST(RandTest, OverloadedRandIntReturnsZeroToMax)
{
	Rand r1;
	int foo[6] = {false};
	int iters = 1000;

	for(int i = 0; i < iters; i++)
	{
		foo[r1.randInt(5)] = true;
	}

	for(int i = 0; i < 6; i++)
	{
		EXPECT_TRUE(foo[i]);
	}
}

TEST(RandTest, CopiedGeneratorMatchesOriginal)
{
	Rand r1;
	int iters = 100;

	//Distance ourselves from the original/default state
	for(int i = 0; i < iters; i++)
	{
		r1.randBit();
	}

	//Now copy and then verify
	Rand r2(r1);
	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.randBit(), r2.randBit());
	}
}

TEST(RandTest, AssignedGeneratorMatchesOriginal)
{
	Rand r1;
	int iters = 100;

	//Distance ourselves from the original/default state
	for(int i = 0; i < iters; i++)
	{
		r1.randBit();
	}

	//Now assign and then verify
	Rand r2;
	r2 = r1;
	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.randBit(), r2.randBit());
	}
}

TEST(RandTest, ConstructGeneratorByRegisters)
{
	Rand r1;
	int iters = 100;

	//Distance ourselves from the original/default state
	for(int i = 0; i < iters; i++)
	{
		r1.randBit();
	}

	//Now get the registers
	uint32_t regA, regB, regC;
	r1.getRegisters(regA, regB, regC);
	Rand r2(regA, regB, regC);
	for(int i = 0; i < iters; i++)
	{
		ASSERT_EQ(r1.randBit(), r2.randBit());
	}
}

TEST(RandTest, RegistersDontZeroOut)
{
	//This seed is carefully chosen to cause the 29-bit register to become
	//0 after a single iteration if the full 32-bit value is used
	uint32_t seed = 0x20000005u;
	Rand r1(seed);

	r1.randBit();

	uint32_t reg_a, reg_b, reg_c;
	r1.getRegisters(reg_a, reg_b, reg_c);

	EXPECT_LT(0, reg_a);
	EXPECT_LT(0, reg_b);
	EXPECT_LT(0, reg_c);
}

TEST(RandTest, HighBitOnlySeedDoesNotZeroRegisters)
{
	//This seed is carefully chosen to cause the 29- and 30-bit registers
	//to become 0 if the high bits are simply masked away.
	//Of course, this actually causes setRegisters to abort, so we actually
	//have to first set known register values, then seed them, then test
	//for inequality against a Rand object we set with the register value as
	//seed (because Rand::setSeed() runs through several iterations of the
	//registers).
	uint32_t seed = (0x1u << 31);
	Rand r1(0xACE, 0xACE, 0xACE);
	Rand r2(0xACE);

	r1.setSeed(seed);

	uint32_t reg_a, reg_b, reg_c;
	r1.getRegisters(reg_a, reg_b, reg_c);
	uint32_t reg2_a, reg2_b, reg2_c;
	r2.getRegisters(reg2_a, reg2_b, reg2_c);

	EXPECT_NE(reg2_a, reg_a);
	EXPECT_NE(reg2_b, reg_b);
	EXPECT_NE(reg2_c, reg_c);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#include "gtest/gtest.h"
#include "actor/Attribute.h"

TEST(AttributeTest, DefaultsToTen)
{
	Attribute a1;

	EXPECT_EQ(10, a1.getMaxAttr());
}

TEST(AttributeTest, SetInitialAttribute)
{
	Attribute a1(15);

	EXPECT_EQ(15, a1.getMaxAttr());
	EXPECT_EQ(15, a1.getCurAttr());
}

TEST(AttributeTest, InitialCurrentEqualToMax)
{
	Attribute a1;

	EXPECT_EQ(a1.getMaxAttr(), a1.getCurAttr());
}

TEST(AttributeTest, ChangeMax)
{
	Attribute a1;
	a1.setMaxAttr(15);

	EXPECT_EQ(15, a1.getMaxAttr());
}

TEST(AttributeTest, ChangeCurrent)
{
	Attribute a1;
	a1.setCurAttr(5);

	EXPECT_EQ(5, a1.getCurAttr());
}


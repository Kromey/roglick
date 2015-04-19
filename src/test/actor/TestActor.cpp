#include "gtest/gtest.h"
#include "actor/Actor.h"

TEST(ActorTest, DisplayCharacter)
{
	Actor a1('@', "Test Actor", 0x00);

	EXPECT_EQ('@', a1.getDisplay());
}


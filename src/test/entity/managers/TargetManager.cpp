#include "gtest/gtest.h"
#include "entity/managers/TargetManager.h"

TEST(TargetManagerTest, TargetManagerIsCorrectType)
{
	TargetManager tm;

	EXPECT_EQ(Target, tm.getComponentType());
}

TEST(TargetManagerTest, EntityDoesNotHaveComponent)
{
	TargetManager tm;
	Entity e = 5;

	EXPECT_FALSE(tm.entityHasComponent(e));
}

TEST(TargetManagerTest, AddedEntityHasComponent)
{
	TargetManager tm;
	Entity e = 5;

	tm.addComponent(e);

	EXPECT_TRUE(tm.entityHasComponent(e));
}

TEST(TargetManagerTest, RemoveComponent)
{
	TargetManager tm;
	Entity e = 5;

	tm.addComponent(e);

	ASSERT_TRUE(tm.entityHasComponent(e));

	tm.removeComponent(e);

	EXPECT_FALSE(tm.entityHasComponent(e));
}

TEST(TargetManagerTest, TargetDefaultsToNULL)
{
	TargetManager tm;
	Entity e = 5;

	tm.addComponent(e);

	EXPECT_EQ(TargetManager::NULL_TARGET.target, tm.getTarget(e).target);
}

TEST(TargetManagerTest, SetTarget)
{
	TargetManager tm;
	Entity e = 5;
	Entity et = 7;
	TargetComponent target = { et };

	tm.setTarget(e, target);

	EXPECT_EQ(target.target, tm.getTarget(e).target);
}


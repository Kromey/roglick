#include "gtest/gtest.h"
#include "entity/components/PositionManager.h"

TEST(PositionManagerTest, PositionManagerIsCorrectType)
{
	PositionManager pm;

	EXPECT_EQ(Position, pm.getComponentType());
}

TEST(PositionManagerTest, EntityDoesNotHaveComponent)
{
	PositionManager pm;
	Entity e = 5;

	EXPECT_FALSE(pm.entityHasComponent(e));
}

TEST(PositionManagerTest, AddedEntityHasComponent)
{
	PositionManager pm;
	Entity e = 5;

	pm.addComponent(e);

	EXPECT_TRUE(pm.entityHasComponent(e));
}

TEST(PositionManagerTest, RemoveComponent)
{
	PositionManager pm;
	Entity e = 5;

	pm.addComponent(e);

	ASSERT_TRUE(pm.entityHasComponent(e));

	pm.removeComponent(e);

	EXPECT_FALSE(pm.entityHasComponent(e));
}

TEST(PositionManagerTest, PositionDefaultsToNULL)
{
	PositionManager pm;
	Entity e = 5;

	pm.addComponent(e);

	EXPECT_EQ(PositionManager::NULL_POS.x, pm.getPosition(e).x);
	EXPECT_EQ(PositionManager::NULL_POS.y, pm.getPosition(e).y);

	EXPECT_EQ(PositionManager::NULL_POS.x, pm.getX(e));
	EXPECT_EQ(PositionManager::NULL_POS.y, pm.getY(e));
}

TEST(PositionManagerTest, SetPosition)
{
	PositionManager pm;
	Entity e = 5;
	PositionComponent pos = {4, 2};

	pm.addComponent(e);
	pm.setPosition(e, pos);

	EXPECT_EQ(pos.x, pm.getPosition(e).x);
	EXPECT_EQ(pos.y, pm.getPosition(e).y);

	EXPECT_EQ(pos.x, pm.getX(e));
	EXPECT_EQ(pos.y, pm.getY(e));
}

TEST(PositionManagerTest, SetPositionByCoordinate)
{
	PositionManager pm;
	Entity e = 5;

	pm.addComponent(e);
	pm.setX(e, 4);
	pm.setY(e, 2);

	EXPECT_EQ(4, pm.getPosition(e).x);
	EXPECT_EQ(2, pm.getPosition(e).y);

	EXPECT_EQ(4, pm.getX(e));
	EXPECT_EQ(2, pm.getY(e));
}


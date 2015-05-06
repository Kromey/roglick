#include "gtest/gtest.h"
#include "entity/components/PositionManager.h"

TEST(PositionManagerTest, PositionComponentComparisons)
{
	PositionComponent p1 = { 3, 4 };
	PositionComponent p2 = { 3, 4 };
	PositionComponent p3 = { 3, 5 };

	EXPECT_TRUE(p1 == p2);
	EXPECT_FALSE(p1 == p3);

	EXPECT_FALSE(p1 != p2);
	EXPECT_TRUE(p1 != p3);
}

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

	pm.setX(e, 4);
	pm.setY(e, 2);

	EXPECT_EQ(4, pm.getPosition(e).x);
	EXPECT_EQ(2, pm.getPosition(e).y);

	EXPECT_EQ(4, pm.getX(e));
	EXPECT_EQ(2, pm.getY(e));
}

TEST(PositionManagerTest, FindEntityByPosition)
{
	PositionManager pm;
	Entity e1 = 5;
	Entity e2 = 7;
	PositionComponent pos1 = { 4, 2 };
	PositionComponent pos2 = { 3, 5 };
	PositionComponent pos3 = { 5, 5 };

	pm.setPosition(e1, pos1);
	pm.setPosition(e2, pos2);

	EXPECT_TRUE(pm.isPositionOccupied(pos1));
	EXPECT_TRUE(pm.isPositionOccupied(pos2));
	EXPECT_TRUE(pm.isPositionOccupied(4, 2));
	EXPECT_TRUE(pm.isPositionOccupied(3, 5));

	EXPECT_FALSE(pm.isPositionOccupied(pos3));
	EXPECT_FALSE(pm.isPositionOccupied(5, 5));

	EXPECT_EQ(e1, pm.getEntityAtPosition(pos1));
	EXPECT_EQ(e1, pm.getEntityAtPosition(4, 2));
	EXPECT_EQ(e2, pm.getEntityAtPosition(pos2));
	EXPECT_EQ(e2, pm.getEntityAtPosition(3, 5));
}


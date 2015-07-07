#include "gtest/gtest.h"
#include "entity/managers/ActionPointManager.h"

TEST(ActionPointManagerTest, ActionPointManagerIsCorrectType)
{
	ActionPointManager sm;

	EXPECT_EQ(ActionPoints, sm.getComponentType());
}

TEST(ActionPointManagerTest, EntityDoesNotHaveComponent)
{
	ActionPointManager sm;
	Entity e = 5;

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, AddedEntityHasComponent)
{
	ActionPointManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_TRUE(sm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, RemoveComponent)
{
	ActionPointManager sm;
	Entity e = 5;

	sm.addComponent(e);

	ASSERT_TRUE(sm.entityHasComponent(e));

	sm.removeComponent(e);

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, ActionPointDefaultsToNULL)
{
	ActionPointManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_EQ(ActionPointManager::NULL_ACTIONPOINT, sm.getComponent(e));
}

TEST(ActionPointManagerTest, SetActionPoint)
{
	ActionPointManager sm;
	Entity e = 5;
	ActionPointComponent ap = 12;

	sm.setComponent(e, ap);

	EXPECT_EQ(ap, sm.getComponent(e));
}


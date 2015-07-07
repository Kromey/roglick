#include "gtest/gtest.h"
#include "entity/managers/ActionPointManager.h"
#include "entity/EntityManager.h"

TEST(ActionPointManagerTest, ActionPointManagerIsCorrectType)
{
	ActionPointManager apm;

	EXPECT_EQ(ActionPoints, apm.getComponentType());
}

TEST(ActionPointManagerTest, EntityDoesNotHaveComponent)
{
	ActionPointManager apm;
	Entity e = 5;

	EXPECT_FALSE(apm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, AddedEntityHasComponent)
{
	ActionPointManager apm;
	Entity e = 5;

	apm.addComponent(e);

	EXPECT_TRUE(apm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, RemoveComponent)
{
	ActionPointManager apm;
	Entity e = 5;

	apm.addComponent(e);

	ASSERT_TRUE(apm.entityHasComponent(e));

	apm.removeComponent(e);

	EXPECT_FALSE(apm.entityHasComponent(e));
}

TEST(ActionPointManagerTest, ActionPointDefaultsToNULL)
{
	ActionPointManager apm;
	Entity e = 5;

	apm.addComponent(e);

	EXPECT_EQ(ActionPointManager::NULL_ACTIONPOINT, apm.getComponent(e));
}

TEST(ActionPointManagerTest, SetActionPoint)
{
	ActionPointManager apm;
	Entity e = 5;
	ActionPointComponent ap = 12;

	apm.setComponent(e, ap);

	EXPECT_EQ(ap, apm.getComponent(e));
}

TEST(ActionPointManagerTest, FilterActionableEntities)
{
	EntityManager em;
	ActionPointManager apm;

	Entity e1 = em.createEntity();
	Entity e2 = em.createEntity();
	Entity e3 = em.createEntity();

	EntityList el1 = apm.filterActionableEntities(em.getEntities());

	EXPECT_EQ(0, el1.size());

	apm.setComponent(e1, 5);
	apm.setComponent(e2, -12);
	apm.setComponent(e3, 7);

	EntityList el2 = apm.filterActionableEntities(em.getEntities());

	EXPECT_EQ(2, el2.size());
}


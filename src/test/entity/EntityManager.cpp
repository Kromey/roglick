#include "gtest/gtest.h"
#include "entity/EntityManager.h"
#include "entity/components/PositionManager.h"

TEST(EntityManagerTest, CreateMultipleEntities)
{
	EntityManager em;

	Entity e1 = em.createEntity();
	Entity e2 = em.createEntity();

	EXPECT_NE(e1, e2);
}

TEST(EntityManagerTest, NewEntitiesAreAlive)
{
	EntityManager em;

	Entity e = em.createEntity();

	EXPECT_TRUE(em.isEntityAlive(e));
}

TEST(EntityManagerTest, DestroyedEntitiesAreNotAlive)
{
	EntityManager em;

	Entity e = em.createEntity();
	em.destroyEntity(e);

	EXPECT_FALSE(em.isEntityAlive(e));
}

TEST(EntityManagerTest, RetrieveComponentManagerByType)
{
	EntityManager em;
	PositionManager cm;

	em.addComponentManager(&cm);

	EXPECT_EQ(&cm, em.getComponentManager(Position));
}

TEST(EntityManagerTest, NoMatchingComponentGetsNULL)
{
	EntityManager em;
	PositionManager cm;

	EXPECT_EQ(NULL, em.getComponentManager(Position));

	em.addComponentManager(&cm);

	EXPECT_EQ(NULL, em.getComponentManager(Sprite));
}


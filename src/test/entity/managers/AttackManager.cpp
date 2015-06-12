#include "gtest/gtest.h"
#include "entity/managers/AttackManager.h"

TEST(AttackManagerTest, AttackManagerIsCorrectType)
{
	AttackManager am;

	EXPECT_EQ(Attack, am.getComponentType());
}

TEST(AttackManagerTest, EntityDoesNotHaveComponent)
{
	AttackManager am;
	Entity e = 5;

	EXPECT_FALSE(am.entityHasComponent(e));
}

TEST(AttackManagerTest, AddedEntityHasComponent)
{
	AttackManager am;
	Entity e = 5;

	am.addComponent(e);

	EXPECT_TRUE(am.entityHasComponent(e));
}

TEST(AttackManagerTest, RemoveComponent)
{
	AttackManager am;
	Entity e = 5;

	am.addComponent(e);

	ASSERT_TRUE(am.entityHasComponent(e));

	am.removeComponent(e);

	EXPECT_FALSE(am.entityHasComponent(e));
}

TEST(AttackManagerTest, AttackDefaultsToNULL)
{
	AttackManager am;
	Entity e = 5;

	am.addComponent(e);

	EXPECT_EQ(AttackManager::NULL_ATTACK.target, am.getComponent(e).target);
}

TEST(AttackManagerTest, SetAttack)
{
	AttackManager am;
	Entity e = 5;
	Entity et = 7;
	AttackComponent target = { et, Swords };

	am.setComponent(e, target);

	EXPECT_EQ(target.target, am.getComponent(e).target);
}


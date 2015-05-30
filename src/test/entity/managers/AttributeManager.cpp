#include "gtest/gtest.h"
#include "entity/managers/AttributeManager.h"

TEST(AttributeManagerTest, AttributeManagerIsCorrectType)
{
	AttributeManager am;

	EXPECT_EQ(Attribute, am.getComponentType());
}

TEST(AttributeManagerTest, EntityDoesNotHaveComponent)
{
	AttributeManager am;
	Entity e = 5;

	EXPECT_FALSE(am.entityHasComponent(e));
}

TEST(AttributeManagerTest, AddedEntityHasComponent)
{
	AttributeManager am;
	Entity e = 5;

	am.addComponent(e);

	EXPECT_TRUE(am.entityHasComponent(e));
}

TEST(AttributeManagerTest, RemoveComponent)
{
	AttributeManager am;
	Entity e = 5;

	am.addComponent(e);

	ASSERT_TRUE(am.entityHasComponent(e));

	am.removeComponent(e);

	EXPECT_FALSE(am.entityHasComponent(e));
}

TEST(AttributeManagerTest, AttributeDefaultsToNULL)
{
	AttributeManager am;
	Entity e = 5;

	am.addComponent(e);

	EXPECT_EQ(am.getNullComponent().size(), am.getComponent(e).size());
}

TEST(AttributeManagerTest, SetAttribute)
{
	AttributeManager am;
	Entity e = 5;
	AttributeComponent strength = {1,2};
	AttributeComponent intelligence = {5,4};

	am.setComponent(e, Str, strength);
	am.setComponent(e, Int, intelligence);

	EXPECT_EQ(strength.max, am.getComponent(e, Str).max);
	EXPECT_EQ(strength.cur, am.getComponent(e, Str).cur);

	EXPECT_EQ(intelligence.max, am.getComponent(e, Int).max);
	EXPECT_EQ(intelligence.cur, am.getComponent(e, Int).cur);

	++strength.max;
	++strength.cur;
	++intelligence.max;
	++intelligence.cur;

	am.setComponent(e, Str, strength);
	am.setComponent(e, Int, intelligence);

	EXPECT_EQ(strength.max, am.getComponent(e, Str).max);
	EXPECT_EQ(strength.cur, am.getComponent(e, Str).cur);

	EXPECT_EQ(intelligence.max, am.getComponent(e, Int).max);
	EXPECT_EQ(intelligence.cur, am.getComponent(e, Int).cur);
}

TEST(AttributeManagerTest, StaminaAndAcuity)
{
	AttributeManager am;
	Entity e = 5;

	AttributeComponent strength = {5, 5};
	AttributeComponent dexterity = {7, 7};

	am.setComponent(e, Str, strength);
	am.setComponent(e, Dex, dexterity);

	EXPECT_EQ(6, am.getComponent(e, Sta).max);

	AttributeComponent intelligence = {5, 5};
	AttributeComponent perception = {7, 7};

	am.setComponent(e, Int, intelligence);
	am.setComponent(e, Per, perception);

	EXPECT_EQ(6, am.getComponent(e, Acu).max);
}


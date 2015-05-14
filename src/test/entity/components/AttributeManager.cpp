#include "gtest/gtest.h"
#include "entity/components/AttributeManager.h"

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

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Str.max, am.getAttribute(e).Str.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Str.cur, am.getAttribute(e).Str.cur);

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Dex.max, am.getAttribute(e).Dex.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Dex.cur, am.getAttribute(e).Dex.cur);

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Sta.max, am.getAttribute(e).Sta.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Sta.cur, am.getAttribute(e).Sta.cur);

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Int.max, am.getAttribute(e).Int.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Int.cur, am.getAttribute(e).Int.cur);

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Per.max, am.getAttribute(e).Per.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Per.cur, am.getAttribute(e).Per.cur);

	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Acu.max, am.getAttribute(e).Acu.max);
	EXPECT_EQ(AttributeManager::NULL_ATTRIBUTE.Acu.cur, am.getAttribute(e).Acu.cur);
}

TEST(AttributeManagerTest, SetAttribute)
{
	AttributeManager am;
	Entity e = 5;
	AttributeComponent attrs = {{1,2},{3,4},{5,6},{7,8},{9,0},{1,2}};

	am.setAttribute(e, attrs);

	EXPECT_EQ(attrs.Str.max, am.getAttribute(e).Str.max);
	EXPECT_EQ(attrs.Str.cur, am.getAttribute(e).Str.cur);

	EXPECT_EQ(attrs.Dex.max, am.getAttribute(e).Dex.max);
	EXPECT_EQ(attrs.Dex.cur, am.getAttribute(e).Dex.cur);

	//The omission of Sta and Acu in this test is deliberate; they are calculated
	//values and will be tested separately.

	EXPECT_EQ(attrs.Int.max, am.getAttribute(e).Int.max);
	EXPECT_EQ(attrs.Int.cur, am.getAttribute(e).Int.cur);

	EXPECT_EQ(attrs.Per.max, am.getAttribute(e).Per.max);
	EXPECT_EQ(attrs.Per.cur, am.getAttribute(e).Per.cur);
}

TEST(AttributeManagerTest, StaminaAndAcuity)
{
	AttributeManager am;
	Entity e = 5;

	AttributeVal strength = {5, 5};
	AttributeVal dexterity = {7, 7};

	am.setAttribute(e, Str, strength);
	am.setAttribute(e, Dex, dexterity);

	EXPECT_EQ(6, am.getAttribute(e, Sta).max);

	AttributeVal intelligence = {5, 5};
	AttributeVal perception = {7, 7};

	am.setAttribute(e, Int, intelligence);
	am.setAttribute(e, Per, perception);

	EXPECT_EQ(6, am.getAttribute(e, Acu).max);
}


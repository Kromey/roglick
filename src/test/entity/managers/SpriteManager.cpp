#include "gtest/gtest.h"
#include "entity/managers/SpriteManager.h"

TEST(SpriteManagerTest, SpriteManagerIsCorrectType)
{
	SpriteManager sm;

	EXPECT_EQ(Sprite, sm.getComponentType());
}

TEST(SpriteManagerTest, EntityDoesNotHaveComponent)
{
	SpriteManager sm;
	Entity e = 5;

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SpriteManagerTest, AddedEntityHasComponent)
{
	SpriteManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_TRUE(sm.entityHasComponent(e));
}

TEST(SpriteManagerTest, RemoveComponent)
{
	SpriteManager sm;
	Entity e = 5;

	sm.addComponent(e);

	ASSERT_TRUE(sm.entityHasComponent(e));

	sm.removeComponent(e);

	EXPECT_FALSE(sm.entityHasComponent(e));
}

TEST(SpriteManagerTest, SpriteDefaultsToNULL)
{
	SpriteManager sm;
	Entity e = 5;

	sm.addComponent(e);

	EXPECT_EQ(SpriteManager::NULL_SPRITE.c, sm.getComponent(e).c);
	EXPECT_EQ(SpriteManager::NULL_SPRITE.attributes, sm.getComponent(e).attributes);
	EXPECT_EQ(SpriteManager::NULL_SPRITE.color, sm.getComponent(e).color);
}

TEST(SpriteManagerTest, SetSprite)
{
	SpriteManager sm;
	Entity e = 5;
	SpriteComponent sprite = {'@', 4, 2};

	sm.setComponent(e, sprite);

	EXPECT_EQ(sprite.c, sm.getComponent(e).c);
	EXPECT_EQ(sprite.attributes, sm.getComponent(e).attributes);
	EXPECT_EQ(sprite.color, sm.getComponent(e).color);
}


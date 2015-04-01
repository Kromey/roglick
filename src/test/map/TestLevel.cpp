#include <stdexcept>

#include "gtest/gtest.h"
#include "map/Level.h"
#include "map/Tile.h"

TEST(LevelTest, DefaultLevelIsWalls)
{
	Level l1(10, 10);

	EXPECT_EQ(WallTile, l1.getTile(5, 5));
}

TEST(LevelTest, LevelGetTile)
{
	Level l1(10, 10);

	EXPECT_NO_THROW(l1.getTile(5, 5));
	EXPECT_THROW(l1.getTile(50, 50), std::out_of_range);
}

TEST(LevelTest, LevelArrayAccess)
{
	Level l1(10, 10);

	EXPECT_NO_THROW(l1[5][5]);
	EXPECT_THROW(l1[50][50], std::out_of_range);
}


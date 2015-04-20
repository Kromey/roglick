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

	EXPECT_NO_THROW(l1.getTile(0, 0));
	EXPECT_NO_THROW(l1.getTile(9, 9));
	EXPECT_THROW(l1.getTile(10, 10), std::out_of_range);
}

TEST(LevelTest, LevelSetTile)
{
	Level l1(10, 10);

	EXPECT_EQ(WallTile, l1.getTile(0, 0));

	l1.setTile(0, 0, FloorTile);

	EXPECT_EQ(FloorTile, l1.getTile(0, 0));
}

TEST(LevelTest, LevelArrayAccess)
{
	Level l1(10, 10);

	EXPECT_NO_THROW(l1[0][0]);
	EXPECT_NO_THROW(l1[9][9]);
	EXPECT_THROW(l1[10][10], std::out_of_range);
}


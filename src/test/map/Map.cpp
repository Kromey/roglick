#include <stdexcept>

#include "gtest/gtest.h"
#include "map/Map.h"
#include "map/Tile.h"

TEST(MapTest, DefaultMapIsWalls)
{
	Map m1(10, 10);

	EXPECT_EQ(WallTile, m1.getTile(5, 5));
}

TEST(MapTest, MapGetTile)
{
	Map m1(10, 10);

	EXPECT_NO_THROW(m1.getTile(0, 0));
	EXPECT_NO_THROW(m1.getTile(9, 9));
	EXPECT_THROW(m1.getTile(10, 10), std::out_of_range);
}

TEST(MapTest, MapSetTile)
{
	Map m1(10, 10);

	EXPECT_EQ(WallTile, m1.getTile(0, 0));

	m1.setTile(0, 0, FloorTile);

	EXPECT_EQ(FloorTile, m1.getTile(0, 0));
}

TEST(MapTest, MapArrayAccess)
{
	Map m1(10, 10);

	EXPECT_NO_THROW(m1[0][0]);
	EXPECT_NO_THROW(m1[9][9]);
	EXPECT_THROW(m1[10][10], std::out_of_range);
}


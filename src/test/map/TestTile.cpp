#include "gtest/gtest.h"
#include "map/Tile.h"

//Simplify our references
using namespace map;

TEST(TileTest, WallTileIsOpaque)
{
	Tile t1 = WallTile;

	EXPECT_FALSE(t1.getTransparent());
}

TEST(TileTest, WallTileIsInpassable)
{
	Tile t1 = WallTile;

	EXPECT_FALSE(t1.getPassable());
}


#include "gtest/gtest.h"
#include "map/Tile.h"

//Simplify our references
using namespace map;

TEST(TileTest, DefaultTileIsWall)
{
	Tile t1;

	EXPECT_FALSE(t1.getTransparent());
	EXPECT_FALSE(t1.getPassable());
}


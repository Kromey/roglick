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

TEST(TileTest, FloorTileIsTransparent)
{
	Tile t1 = FloorTile;

	EXPECT_TRUE(t1.getTransparent());
}

TEST(TileTest, FloorTileIsPassable)
{
	Tile t1 = FloorTile;

	EXPECT_TRUE(t1.getPassable());
}

TEST(TileTest, ClosedDoorTileIsOpaque)
{
	Tile t1 = ClosedDoorTile;

	EXPECT_FALSE(t1.getTransparent());
}

TEST(TileTest, ClosedDoorTileIsInpassable)
{
	Tile t1 = ClosedDoorTile;

	EXPECT_FALSE(t1.getPassable());
}

TEST(TileTest, OpenDoorTileIsTransparent)
{
	Tile t1 = OpenDoorTile;

	EXPECT_TRUE(t1.getTransparent());
}

TEST(TileTest, OpenDoorTileIsPassable)
{
	Tile t1 = OpenDoorTile;

	EXPECT_TRUE(t1.getPassable());
}


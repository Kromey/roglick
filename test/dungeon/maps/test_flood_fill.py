from roglick.dungeon.base import Map,Tile
from roglick.dungeon import tiles
from roglick.engine import random


def test_flood_fill_returns_cells_once():
    m = Map(50,50, random.Random())
    for x in range(1,50):
        for y in range(1,50):
            m.tiles[x][y] = Tile(**tiles.floor)

    cells = [cell for cell in m.flood_fill(6,6)]

    while 0 < len(cells):
        cell = cells.pop()
        assert cell not in cells

def test_flood_fill_fills_area():
    m = Map(50,50, random.Random())
    for x in range(50):
        for y in range(50):
            m.tiles[x][y] = Tile(**tiles.floor)

    cells = [cell for cell in m.flood_fill(6,6)]

    assert 50*50 == len(cells)


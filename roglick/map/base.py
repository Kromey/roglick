import roglick.lib.libtcodpy as libtcod
from . import tiles


class Tile(object):
    def __init__(self, glyph, is_passable=False, is_transparent=False, color_lit=libtcod.white, color_unlit=libtcod.gray):
        self.glyph = glyph
        self.is_passable = is_passable
        self.is_transparent = is_transparent
        self.color_lit = color_lit
        self.color_unlit = color_unlit


class Map(object):
    def __init__(self, width, height, fill=tiles.WallTile):
        self._width = width
        self._height = height

        self.tiles = [[Tile(**fill) for y in range(self._height)]
                for x in range(self._width)]

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height


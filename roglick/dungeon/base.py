import roglick.lib.libtcodpy as libtcod
from . import tiles


class Tile(object):
    def __init__(self, glyph, is_passable=False, is_transparent=None, color_lit=libtcod.white, color_unlit=libtcod.gray):
        self.glyph = glyph
        self.is_passable = is_passable
        if is_transparent is None:
            # By default, impassable Tiles are non-transparent, and vice-versa
            is_transparent = is_passable
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


class Room(object):
    def __init__(self, x, y, width, height):
        self.x1 = x
        self.y1 = y
        self.x2 = x + width
        self.y2 = y + height

    def intersects(self, other):
        # Returns true if this room intersects with another one
        return (self.x1 <= other.x2 and self.x2 >= other.x1 and
                self.y1 <= other.y2 and self.y2 >= other.y1)


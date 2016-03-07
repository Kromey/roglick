import roglick.lib.libtcodpy as libtcod
from roglick.ecs.base import Component


class PositionComponent(Component):
    __slots__ = ('x', 'y')
    def __init__(self, x, y):
        self.x = x
        self.y = y


class SpriteComponent(Component):
    __slots__ = ('glyph', 'color')
    def __init__(self, glyph, color=libtcod.white):
        self.glyph = glyph
        self.color = color


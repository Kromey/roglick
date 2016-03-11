from roglick.lib import libtcod
from roglick.engine.ecs import Component


class PositionComponent(Component):
    __slots__ = ('x', 'y')
    def __init__(self, x, y):
        self.x = int(x)
        self.y = int(y)


class SpriteComponent(Component):
    __slots__ = ('glyph', 'color')
    def __init__(self, glyph, color=libtcod.white):
        self.glyph = glyph
        self.color = color


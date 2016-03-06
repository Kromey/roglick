from .ecs.base import Component


class PositionComponent(Component):
    def __init__(self, x, y):
        self.x = x
        self.y = y


class SpriteComponent(Component):
    def __init__(self, glyph):
        self.glyph = glyph


from roglick.lib import libtcod
from roglick.engine import colors
from roglick.engine.ecs import Component


class PositionComponent(Component):
    _properties = (('x', 0), ('y', 0))


class SpriteComponent(Component):
    _properties = (('glyph', ' '), ('color', colors.white))


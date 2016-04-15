from roglick.engine import colors
from roglick.engine.ecs import ComponentBase


class PositionComponent(ComponentBase):
    _properties = (('x', 0), ('y', 0))


class SpriteComponent(ComponentBase):
    _properties = (('glyph', ' '), ('color', colors.white))


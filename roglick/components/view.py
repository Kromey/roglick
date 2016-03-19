from roglick.engine.ecs import Component


class FoVComponent(Component):
    __slots__ = ('x', 'y', 'fov')
    def __init__(self):
        self.x = None
        self.y = None
        self.fov = None


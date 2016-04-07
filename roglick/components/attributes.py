from roglick.engine.ecs import Component


class AttributesComponent(Component):
    __slots__ = ('str','dex','int','per')
    def __init__(self, str=10, dex=10, int=10, per=10):
        self.str = str
        self.dex = dex
        self.int = int
        self.per = per


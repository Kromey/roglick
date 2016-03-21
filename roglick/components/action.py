from roglick.engine.ecs import Component


class FatigueComponent(Component):
    __slots__ = ('fatigue')
    def __init__(self):
        self.fatigue = 0


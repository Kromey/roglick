from roglick.engine.ecs import Component, MultiComponent


class SkillSubComponent(Component):
    __slots__ = ('ranks', 'xp')
    def __init__(self, ranks=0, xp=0):
        self.ranks = ranks
        self.xp = xp


class SkillsComponent(MultiComponent):
    pass


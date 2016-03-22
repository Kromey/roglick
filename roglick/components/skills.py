from roglick.engine.ecs import Component


class SkillSubComponent(Component):
    __slots__ = ('ranks', 'xp')
    def __init__(self, attr, parent=None):
        self.ranks = ranks
        self.xp = xp


class SkillComponent(Component):
    __slots__ = ('__dict__') #TODO: Is this the best approach?
    def __init__(self, **kwargs):
        for skill in kwargs:
            key = skill.lower().replace(' ', '_')
            setattr(self, key, SkillSubComponent(**kwargs[skill]))


from roglick.engine.ecs import Component


class SkillSubComponent(Component):
    __slots__ = ('parent', 'attr')
    def __init__(self, attr, parent=None):
        self.attr = attr
        self.parent = parent


class SkillComponent(Component):
    __slots__ = ('__dict__') #TODO: Is this the best approach?
    def __init__(self, **kwargs):
        for skill in kwargs:
            key = skill.lower().replace(' ', '_')
            setattr(self, key, SkillSubComponent(**kwargs[skill]))


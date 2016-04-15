from roglick.engine.ecs import MultiComponentBase


class SkillsComponent(MultiComponentBase):
    _properties = (('ranks', 0), ('xp', 0))


from roglick.engine.ecs import Component


class SkillsComponent(Component, dict):
    _properties = ()
    class Skill(Component):
        _properties = (('ranks', 0), ('xp', 0))


from roglick.engine.ecs import MultiComponent


class SkillsComponent(MultiComponent):
    _properties = (('ranks', 0), ('xp', 0))


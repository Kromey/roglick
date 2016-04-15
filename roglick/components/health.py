from roglick.engine.ecs import Component


class HealthComponent(Component):
    _properties = (('hp', 0), ('mp', 0), ('max_hp', 0), ('max_mp', 0))


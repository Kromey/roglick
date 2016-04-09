from roglick.engine.ecs import Component


class HealthComponent(Component):
    __slots__ = ('hp','mp', 'max_hp', 'max_mp')
    def __init__(self, max_hp, max_mp):
        self.max_hp = max_hp
        self.hp = max_hp

        self.max_mp = max_mp
        self.mp = max_mp


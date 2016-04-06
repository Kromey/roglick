from roglick.engine.event import Event


class CombatEvent(Event):
    def __init__(self, entity, defender, x, y):
        super().__init__(entity=entity)

        self.defender = defender
        self.x = x
        self.y = y

    def __repr__(self):
        return "{cls}({e}, {d}, {x}, {y})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                d=self.defender,
                x=self.x,
                y=self.y)


class AttackEvent(CombatEvent):
    pass


class HitEvent(CombatEvent):
    def __init__(self, entity, defender, x, y, atk_dos):
        super().__init__(
                entity=entity,
                defender=defender,
                x=x, y=y)

        self.atk_dos = atk_dos

    def __repr__(self):
        return "{cls}({e}, {d}, {x}, {y}, {a})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                d=self.defender,
                x=self.x,
                y=self.y,
                a=self.atk_dos)


class DamageEvent(CombatEvent):
    def __init__(self, entity, defender, x, y, dmg):
        super().__init__(
                entity=entity,
                defender=defender,
                x=x, y=y)

        self.dmg = dmg

    def __repr__(self):
        return "{cls}({e}, {d}, {x}, {y}, {dmg})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                d=self.defender,
                x=self.x,
                y=self.y,
                dmg=self.dmg)


class PenetratingDamageEvent(CombatEvent):
    def __init__(self, entity, defender, x, y, dmg):
        super().__init__(
                entity=entity,
                defender=defender,
                x=x, y=y)

        self.dmg = dmg

    def __repr__(self):
        return "{cls}({e}, {d}, {x}, {y}, {dmg})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                d=self.defender,
                x=self.x,
                y=self.y,
                dmg=self.dmg)


import collections


from roglick.engine.event import Event


class NewMapEvent(Event):
    pass


class MapChangedEvent(Event):
    pass


class QuitEvent(Event):
    pass


class PreInputEvent(Event):
    pass


class MoveEvent(Event):
    def __init__(self, entity, dx, dy):
        super().__init__(entity=entity)

        self.dx = dx
        self.dy = dy

    def __repr__(self):
        return "{cls}({e}, {dx}, {dy})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                dx=self.dx,
                dy=self.dy)


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


class ClimbEvent(Event):
    pass


class ClimbDownEvent(ClimbEvent):
    pass


class ClimbUpEvent(ClimbEvent):
    pass


class OpenDoorEvent(Event):
    def __init__(self, entity, x, y):
        super().__init__(entity=entity)

        self.x = x
        self.y = y

    def __repr__(self):
        return "{cls}({e}, {x}, {y})".format(
                cls=self.__class__.__name__,
                e=self.entity,
                x=self.x,
                y=self.y)


class ActionCompleteEvent(Event):
    def __init__(self, entity, fatigue_cost, apply_speed=True):
        super().__init__(entity=entity)

        self.fatigue_cost = fatigue_cost
        self.apply_speed = apply_speed

    def __repr__(self):
        if self.apply_speed:
            # Don't bother with apply_speed parameter if it's still default
            return "{cls}({e}, {cost})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    cost=self.fatigue_cost)
        else:
            return "{cls}({e}, {cost}, False)".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    cost=self.fatigue_cost)


class SkillCheckEvent(Event):
    Result = collections.namedtuple(
            'Result',
            ['success', 'critical', 'roll', 'dos'])

    def __init__(self, entity, skill, modifier=0):
        super().__init__(entity=entity)

        self.skill = skill
        self.modifier = modifier
        self.result = None

    def __repr__(self):
        if self.result is None:
            return "{cls}({e}, {s}, {m:+})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    s=self.skill,
                    m=self.modifier)
        else:
            return "{cls}({e}, {s}, {m:+}, {r})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    s=self.skill,
                    m=self.modifier,
                    r=self.result)


class MessageEvent(Event):
    def __init__(self, msg):
        super().__init__(entity=None)

        self.msg = msg

    def __repr__(self):
        return "{cls}({msg})".format(
                cls=self.__class__.__name__,
                msg=self.msg)


from roglick.engine.event import Event


class CombatEvent(Event):
    class Damage(object):
        __slots__ = ('piercing', 'bludgeoning', 'slashing', 'impaling')
        def __init__(self,
                piercing=0,
                bludgeoning=0,
                slashing=0,
                impaling=0):

            self.piercing = piercing
            self.bludgeoning = bludgeoning
            self.slashing = slashing
            self.impaling = impaling

        def __repr__(self):
            kwargs = []
            if self.piercing is not None:
                kwargs.append("pi={}".format(self.piercing))
            if self.bludgeoning is not None:
                kwargs.append("bl={}".format(self.bludgeoning))
            if self.slashing is not None:
                kwargs.append("sl={}".format(self.slashing))
            if self.impaling is not None:
                kwargs.append("im={}".format(self.impaling))

            return "{cls}({kwargs})".format(
                    cls=self.__class__.__name__,
                    kwargs=", ".join(kwargs))


    def __init__(self,
            attacker, defender,
            atk_skill=None, atk_mod=0,
            def_skill=None, def_mod=0,
            dmg_mod=None, dmg=None):

        super().__init__(entity=attacker)

        if dmg_mod is None:
            dmg_mod = CombatEvent.Damage()
        if dmg is None:
            dmg = CombatEvent.Damage()

        self.defender = defender
        self.atk_skill = atk_skill
        self.atk_mod = atk_mod
        self.def_skill = def_skill
        self.def_mod = def_mod
        self.dmg_mod = dmg_mod
        self.dmg = dmg

    @property
    def kwargs(self):
        return {
                'attacker': self.entity,
                'defender': self.defender,
                'atk_skill': self.atk_skill,
                'atk_mod': self.atk_mod,
                'def_skill': self.def_skill,
                'def_mod': self.def_mod,
                'dmg_mod': self.dmg_mod,
                'dmg': self.dmg,
                }

    def __repr__(self):
        kwargs = self.kwargs
        args = []
        for key in kwargs:
            if key == 'attacker' or key == 'defender':
                # We handle these separately to ensure proper order
                continue

            if kwargs[key] is not None and kwargs[key] != 0:
                args.append("{key}={val}".format(key=key, val=kwargs[key]))

        args = ", ".join(args)

        if len(args) > 0:
            return "{cls}({e}, {d}, {kwargs})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    d=self.defender,
                    kwargs=args)
        else:
            return "{cls}({e}, {d})".format(
                    cls=self.__class__.__name__,
                    e=self.entity,
                    d=self.defender)


class AttackEvent(CombatEvent):
    pass


class HitEvent(CombatEvent):
    pass


class DamageEvent(CombatEvent):
    pass


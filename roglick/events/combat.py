from roglick.engine.event import Event


class CombatEvent(Event):
    def __init__(self,
            attacker, defender,
            atk_skill=None, atk_mod=0,
            def_skill=None, def_mod=0,
            dmg_mod=0, dmg=None):

        super().__init__(entity=attacker)

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


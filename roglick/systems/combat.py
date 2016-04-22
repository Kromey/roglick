from roglick.engine.ecs import SystemBase, exceptions
from roglick.engine import event, random
from roglick import events


class CombatSystem(SystemBase):
    @event.event_handler(events.AttackEvent)
    def attack_handler(self, atk_event):
        atk_check = events.SkillCheckEvent(
                atk_event.entity, 'melee.swords.short_sword')
        event.dispatch(atk_check)

        if atk_check.result.success:
            hit_event = events.HitEvent(**atk_event.kwargs)
            hit_event.def_mod = atk_check.result.dos

            event.dispatch(hit_event)
        else:
            event.dispatch(events.MessageEvent("You missed!"))

    @event.event_handler(events.HitEvent)
    def hit_handler(self, hit_event):
        def_check = events.SkillCheckEvent(
                hit_event.defender, 'melee.shield')
        event.dispatch(def_check)

        if def_check.result.success:
            event.dispatch(events.MessageEvent("It blocked your attack!"))
        else:
            dmg = self._roll_damage(hit_event.entity, hit_event.def_mod)
            dmg_event = events.DamageEvent(**hit_event.kwargs)
            dmg_event.dmg.bludgeoning = dmg

            event.dispatch(dmg_event)

    def _roll_damage(self, attacker, attack_dos):
        # TODO: Actually get attributes; for now, fudge it and pretend Str=10
        strength = 10
        n = max(1, int(strength/5)-1)
        m = 6 + 4 * n

        dmg = random.roll_dice(n) + strength - m

        return dmg


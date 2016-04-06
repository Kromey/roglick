from roglick.engine.ecs import System, exceptions
from roglick.components import SkillComponent
from roglick.engine import event, random
from roglick import events


class CombatSystem(System):
    @event.event_handler(events.AttackEvent)
    def attack_handler(self, atk_event):
        atk_check = events.SkillCheckEvent(
                atk_event.entity, 'melee.swords.short_sword')
        event.dispatch(atk_check)

        if atk_check.result.success:
            event.dispatch(events.HitEvent(
                atk_event.entity, atk_event.defender,
                atk_event.x, atk_event.y, atk_check.result.dos))
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
            dmg = self._roll_damage(hit_event.entity, hit_event.atk_dos)
            event.dispatch(events.DamageEvent(
                hit_event.entity, hit_event.defender,
                hit_event.x, hit_event.y, dmg))

    @event.event_handler(events.DamageEvent)
    def dmg_handler(self, dmg_event):
        # TODO: This method will get the defender's armor and apply DR
        # For now, let's just pretend the defender is naked
        event.dispatch(events.PenetratingDamageEvent(
            dmg_event.entity, dmg_event.defender,
            dmg_event.x, dmg_event.y, dmg_event.dmg))

    @event.event_handler(events.PenetratingDamageEvent)
    def pen_dmg_handler(self, dmg_event):
        # TODO: This method will apply damage to the defender
        # For now, any damage is a kill
        self._entity_manager.destroy_entity(dmg_event.defender)
        # TODO: We'll actually have another system handle destroying entities

    def _roll_damage(self, attacker, attack_dos):
        # TODO: Actually get attributes; for now, fudge it and pretend Str=10
        # NB: This is currently using an alternate damage calculation, which
        # has not yet been settled upon!
        dmg = random.roll_dice() * (10 + attack_dos) / 10

        return dmg


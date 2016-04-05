from roglick.engine.ecs import System, exceptions
from roglick.components import SkillComponent
from roglick.engine import event
from roglick import events


class CombatSystem(System):
    @event.event_handler(events.AttackEvent)
    def attack_handler(self, atk_event):
        atk_check = events.SkillCheckEvent(
                atk_event.entity, 'melee.swords.short_sword')
        event.dispatch(atk_check)


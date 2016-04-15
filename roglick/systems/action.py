from roglick.engine.ecs import SystemBase, exceptions
from roglick.components import FatigueComponent
from roglick.engine import event
from roglick.events import ActionCompleteEvent


class FatigueSystem(SystemBase):
    def execute(self):
        for entity, components in self._entity_manager.get_entities_with_component(
                FatigueComponent):
            fcomp = components[FatigueComponent]

            if fcomp.fatigue > 0:
                fcomp.fatigue = max(0, fcomp.fatigue - 1)

    @event.event_handler(ActionCompleteEvent)
    def action_complete_handler(self, actionevent):
        try:
            fatigue = self._entity_manager.get_component(
                    actionevent.entity, FatigueComponent)
        except exceptions.NoComponentForEntityError:
            # TODO Do we really want to force this onto all Entities that act?
            fatigue = FatigueComponent()
            self._entity_manager.set_component(
                    actionevent.entity, fatigue)

        # TODO Will need to adjust cost per Entity speed, once we have that
        fatigue.fatigue += actionevent.fatigue_cost


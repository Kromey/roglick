from roglick.engine.ecs import System,exceptions
from roglick.engine import event
from roglick.events import SpawnEntityEvent
from roglick.components import AttributesComponent,HealthComponent


class HealthSystem(System):
    @event.event_handler(SpawnEntityEvent)
    def spawn_handler(self, myevent):
        try:
            comps = self._entity_manager.get_component(myevent.entity, AttributesComponent)
        except exceptions.NoComponentForEntity:
            # Entity has no attributes, it gets no health
            return

        attrs = comps[AttributesComponent]

        max_hp = int(5 + attrs.str + attrs.dex/2)
        max_mp = int(5 + attrs.int + attrs.per/2)

        self._entity_manager.set_component(myevent.entity, HealthComponent(max_hp, max_mp))


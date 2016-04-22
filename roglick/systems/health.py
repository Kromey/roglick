from roglick.engine.ecs import SystemBase,exceptions
from roglick.engine import event
from roglick.events import SpawnEntityEvent, DamageEvent, MessageEvent
from roglick.components import AttributesComponent,HealthComponent
from roglick import logging


logger = logging.getLogger(__name__)


class HealthSystem(SystemBase):
    def execute(self):
        # Can't kill an entity while iterating, so stash a list of deadites
        deadites = []

        for entity, components in self._entity_manager.get_entities_with_component(
                HealthComponent):
            health = components[HealthComponent]

            if health.hp <= 0:
                deadites.append(entity)

        for entity in deadites:
            self._entity_manager.destroy_entity(entity)
            event.dispatch(MessageEvent("{} dies!".format(entity)))

    @event.event_handler(SpawnEntityEvent)
    def spawn_handler(self, myevent):
        logger.debug("Processing SpawnEntityEvent for {}".format(myevent.entity))
        try:
            attrs = self._entity_manager.get_component(myevent.entity, AttributesComponent)
        except exceptions.NoComponentForEntityError:
            # Entity has no attributes, it gets no health
            logger.debug("No attributes for {}, no health".format(myevent.entity))
            return

        max_hp = int(5 + attrs.st + attrs.dx/2)
        max_mp = int(5 + attrs.iq + attrs.pe/2)

        self._entity_manager.set_component(myevent.entity, HealthComponent(max_hp, max_mp))
        logger.debug("Set HP to {} and MP to {}".format(max_hp, max_mp))

    @event.event_handler(DamageEvent)
    def dmg_handler(self, dmg_event):
        try:
            health = self._entity_manager.get_component(dmg_event.defender, HealthComponent)
        except exceptions.NoComponentForEntityError:
            # TODO How do we want to handle damaging Entities with no health?
            return

        dmg = 0
        # Different damage types have different multipliers; apply those now
        dmg += dmg_event.dmg.piercing * 0.8
        dmg += dmg_event.dmg.bludgeoning * 1.0
        dmg += dmg_event.dmg.slashing * 1.5
        dmg += dmg_event.dmg.impaling * 2.0

        # Round down any fractions
        dmg = int(dmg)

        # Now reduce damage from HP
        health.hp -= dmg
        # TODO: Temporary debugging log message
        event.dispatch(MessageEvent("You dealt {} damage to it!".format(dmg)))


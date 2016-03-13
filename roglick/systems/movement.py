from roglick.engine.ecs import System
from roglick.components import PositionComponent
from roglick.events import MoveEvent
from roglick.engine import event


class MovementSystem(System):
    def __init__(self):
        super().__init__()
        event.register(self)

    @event.event_handler(MoveEvent)
    def move_handler(self, myevent):
        pos = self._entity_manager.get_component(self._entity_manager.pc, PositionComponent)
        pos.x += myevent.dx
        pos.y += myevent.dy

        return event.DONE


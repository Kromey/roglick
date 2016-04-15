from roglick.engine.ecs import SystemBase
from roglick.components import PositionComponent
from roglick.events import ActionCompleteEvent,MoveEvent
from roglick.engine import event


class MovementSystem(SystemBase):
    def __init__(self):
        super().__init__()

    @event.event_handler(MoveEvent)
    def move_handler(self, myevent):
        pos = self._entity_manager.get_component(self._entity_manager.pc, PositionComponent)
        pos.x += myevent.dx
        pos.y += myevent.dy

        if myevent.dx and myevent.dy:
            # Diagonal movement costs 1,400 Fatigue
            fatigue = 1400
        else:
            # Orthoganal movement costs 1,000 Fatigue
            fatigue = 1000

        event.dispatch(ActionCompleteEvent(myevent.entity, fatigue))


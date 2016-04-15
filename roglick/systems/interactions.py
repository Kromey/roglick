from roglick.dungeon import features
from roglick.engine.ecs import SystemBase
from roglick.engine import event
from roglick.events import ActionCompleteEvent,OpenDoorEvent,MapChangedEvent,MessageEvent


class InteractionSystem(SystemBase):
    @event.event_handler(OpenDoorEvent)
    def open_door_handler(self, openevent):
        # Change the door Feature to an open door
        x, y = openevent.x, openevent.y
        self._world.current_map.tiles[x][y].add_feature(features.open_door)

        # Dispatch a new message
        event.dispatch(MessageEvent("You open the door"))

        # We've changed the map, signal that
        event.dispatch(MapChangedEvent())

        # Now dispatch the ActionCompleteEvent; 1000 Fatigue to open a door
        event.dispatch(ActionCompleteEvent(openevent.entity, 1000))


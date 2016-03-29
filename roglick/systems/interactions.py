from roglick.dungeon import features
from roglick.engine.ecs import System
from roglick.engine import event
from roglick.events import ActionCompleteEvent,OpenDoorEvent


class InteractionSystem(System):
    @event.event_handler(OpenDoorEvent)
    def open_door_handler(self, openevent):
        # Change the door Feature to an open door
        x, y = openevent.x, openevent.y
        self._world.current_map.tiles[x][y].add_feature(features.open_door)

        # Now dispatch the ActionCompleteEvent; 1000 Fatigue to open a door
        event.dispatch(ActionCompleteEvent(openevent.entity, 1000))


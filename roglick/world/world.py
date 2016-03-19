from .dungeon import DungeonManager
from roglick.engine import event,random
from roglick.events import MoveEvent,ClimbDownEvent,ClimbUpEvent


class WorldManager(object):
    """The central manager for maintaining all world data."""
    def __init__(self, entity_manager):
        self._em = entity_manager
        self._dungeon = DungeonManager(self, random.get_int())

    @property
    def current_dungeon(self):
        return self._dungeon

    @property
    def current_map(self):
        return self.current_dungeon.current_level.map

    @event.event_handler(MoveEvent, ClimbDownEvent, ClimbUpEvent)
    def map_handler(self, myevent):
        self.current_dungeon.map_handler(myevent)

from roglick.dungeon.maps import SimpleDungeon
from roglick.engine import event
from roglick.events import MoveEvent
from roglick.components import PositionComponent


class WorldManager(object):
    """The central manager for maintaining all world data."""
    def __init__(self, entity_manager):
        self._em = entity_manager
        self._dungeon = DungeonManager(self)
        event.register(self.map_handler, MoveEvent)

    @property
    def current_dungeon(self):
        return self._dungeon

    @property
    def current_map(self):
        return self.current_dungeon.current_level.map

    def map_handler(self, myevent):
        return self.current_dungeon.map_handler(myevent)


class DungeonManager(object):
    """This object manages all data for a particular dungeon."""
    def __init__(self, world_manager):
        self._wm = world_manager
        self._level = LevelManager(self)

    @property
    def current_level(self):
        return self._level

    def map_handler(self, myevent):
        return self.current_level.map_handler(myevent)


class LevelManager(object):
    """This object manages a single level of a dungeon."""
    def __init__(self, dungeon_manager):
        self._dm = dungeon_manager
        self._map = SimpleDungeon(80, 50)

    @property
    def map(self):
        return self._map

    def map_handler(self, myevent):
        epos = self._dm._wm._em.get_component(myevent.entity_source, PositionComponent)

        tx = epos.x + myevent.dx
        ty = epos.y + myevent.dy

        if not self.map.tiles[tx][ty].is_passable:
            return event.FAILED
        else:
            return event.PASS


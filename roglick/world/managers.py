from roglick.dungeon.maps import SimpleDungeon,ConwayDungeon
from roglick.dungeon import Feature,features
from roglick.engine import event,random
from roglick.events import MoveEvent,ClimbDownEvent,ClimbUpEvent
from roglick.components import PositionComponent


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


class DungeonManager(object):
    """This object manages all data for a particular dungeon."""
    def __init__(self, world_manager, dungeon_seed):
        self._wm = world_manager
        self._random = random.Random(dungeon_seed)

        self._seeds = []
        self._current_level = 0
        self._level = LevelManager(self, self.get_level_seed(self._current_level))

    @property
    def current_level(self):
        return self._level

    def get_level_seed(self, level):
        while len(self._seeds) <= level:
            self._seeds.append(self._random.get_int())

        return self._seeds[level]

    def map_handler(self, myevent):
        self.current_level.map_handler(myevent)


class LevelManager(object):
    """This object manages a single level of a dungeon."""
    def __init__(self, dungeon_manager, level_seed):
        self._dm = dungeon_manager
        self._seed = level_seed

        self._random = random.Random(self._seed)

        if self._random.flip_coin():
            self._map = SimpleDungeon(80, 50, self._random)
        else:
            self._map = ConwayDungeon(80, 50, self._random)

        # Add 2-5 stairs to lower levels
        for n in range(self._random.get_int(2,5)):
            x,y = self._map.get_random_cell()
            self._map.tiles[x][y].add_feature(features.StairsDown)

    @property
    def map(self):
        return self._map

    def map_handler(self, myevent):
        epos = self._dm._wm._em.get_component(myevent.entity_source, PositionComponent)

        if myevent.__class__ == MoveEvent:
            tx = epos.x + myevent.dx
            ty = epos.y + myevent.dy

            if not self.map.tiles[tx][ty].is_passable:
                # Illegal move, prevent this event from continuing
                myevent.stop()
        elif myevent.__class__ == ClimbDownEvent:
            if self.map.tiles[epos.x][epos.y] != Feature(**features.StairsDown):
                # Can't descend without stairs, dummy!
                myevent.stop()


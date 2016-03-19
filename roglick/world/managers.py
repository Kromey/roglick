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
        self._stairs = []
        self._current_level = 0

        self.create_level()

    def create_level(self):
        seed = self.get_level_seed(self._current_level)
        self._level = LevelManager(self, seed)

        stairs = self.get_level_stairs(self._current_level)

        self._level.add_stairs_down(stairs=stairs[0])
        if 0 < self._current_level:
            self._level.add_stairs_up(stairs=stairs[1])

    @property
    def current_level(self):
        return self._level

    def get_level_stairs(self, level):
        if level < 0:
            return [None,None]

        while len(self._stairs) <= level:
            self._stairs.append(self.build_level_stairs(len(self._stairs)))

        return self._stairs[level]

    def build_level_stairs(self, level):
        if level == 0:
            up_stairs = []
        else:
            up_stairs = self._stairs[level - 1][0]

        down_stairs = []
        for n in range(2,5):
            x,y = self.current_level.map.get_random_cell()
            down_stairs.append((x,y))

        return [down_stairs, up_stairs]

    def get_level_seed(self, level):
        while len(self._seeds) <= level:
            self._seeds.append(self._random.get_int())

        return self._seeds[level]

    def map_handler(self, myevent):
        self.current_level.map_handler(myevent)

        # Now we can try to handle stairs, if not stopped
        if myevent.propagate:
            pcpos = self._wm._em.get_component(self._wm._em.pc, PositionComponent)

            if myevent.__class__ == ClimbDownEvent:
                self._current_level += 1
                self.create_level()

                # Now make sure we don't embed the PC in a wall...
                # TODO: We'll want to make sure stairs line up, else regen map
                pcpos.x,pcpos.y = self.current_level.map.get_random_cell()
            if myevent.__class__ == ClimbUpEvent:
                self._current_level = max(0, self._current_level - 1)
                self.create_level()

                # Now make sure we don't embed the PC in a wall...
                # TODO: We'll want to make sure stairs line up, else regen map
                pcpos.x,pcpos.y = self.current_level.map.get_random_cell()


class LevelManager(object):
    """This object manages a single level of a dungeon."""
    def __init__(self, dungeon_manager, level_seed):
        self._dm = dungeon_manager
        self._seed = level_seed

        self._random = random.Random(self._seed)

        self._stairs_down = []
        self._stairs_up = []

        if self._random.flip_coin():
            self._map = SimpleDungeon(80, 50, self._random)
        else:
            self._map = ConwayDungeon(80, 50, self._random)

    def add_stairs_down(self, stairs):
        self._stairs_down = stairs
        for x,y in stairs:
            self._map.tiles[x][y].add_feature(features.StairsDown)

    def add_stairs_up(self, stairs):
        self._stairs_up = stairs
        for x,y in stairs:
            self._map.tiles[x][y].add_feature(features.StairsUp)

    @property
    def map(self):
        return self._map

    @property
    def stairs_down(self):
        return self._stairs_down

    @property
    def stairs_up(self):
        return self._stairs_up

    def map_handler(self, myevent):
        epos = self._dm._wm._em.get_component(myevent.entity_source, PositionComponent)

        if myevent.__class__ == MoveEvent:
            tx = epos.x + myevent.dx
            ty = epos.y + myevent.dy

            if not self.map.tiles[tx][ty].is_passable:
                # Illegal move, prevent this event from continuing
                myevent.stop()
        elif myevent.__class__ == ClimbDownEvent:
            if self.map.tiles[epos.x][epos.y] != features.StairsDown:
                # Can't descend without stairs, dummy!
                myevent.stop()
        elif myevent.__class__ == ClimbUpEvent:
            if self.map.tiles[epos.x][epos.y] != features.StairsUp:
                # Can't ascend without stairs, dummy!
                myevent.stop()


from .level import LevelManager
from roglick.engine import event,random
from roglick.components import PositionComponent
from roglick.events import MoveEvent,ClimbDownEvent,ClimbUpEvent,NewMapEvent


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

        maps = 1
        while not self._level_valid():
            # Didn't get a valid map, re-build it
            print("Discarding map {} and trying again...".format(maps))
            self._level.map.make_map()
            maps += 1

        stairs_up = self.get_level_stairs(self._current_level-1)
        stairs_down = self.get_level_stairs(self._current_level)

        self._level.add_stairs_up(stairs=stairs_up)
        self._level.add_stairs_down(stairs=stairs_down)

        event.dispatch(NewMapEvent())

    @property
    def current_level(self):
        return self._level

    def _level_valid(self):
        # Ensure all stairs go on valid tiles
        stairs = self.get_level_stairs(self._current_level-1)

        for x,y in stairs:
            if not self._level.map.tiles[x][y].is_passable:
                return False

        return True

    def get_level_stairs(self, level):
        if level < 0:
            return []

        while len(self._stairs) <= level:
            self._stairs.append(self.build_level_stairs(len(self._stairs)))

        return self._stairs[level]

    def build_level_stairs(self, level):
        down_stairs = []
        for n in range(2,5):
            x,y = self.current_level.map.get_random_cell()
            down_stairs.append((x,y))

        return down_stairs

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
                pcpos.x,pcpos.y = self.current_level.map.get_random_cell()
            if myevent.__class__ == ClimbUpEvent:
                self._current_level = max(0, self._current_level - 1)
                self.create_level()

                # Now make sure we don't embed the PC in a wall...
                pcpos.x,pcpos.y = self.current_level.map.get_random_cell()

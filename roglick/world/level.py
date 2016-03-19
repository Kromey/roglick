from roglick.engine import random
from roglick.dungeon.maps import SimpleDungeon,ConwayDungeon
from roglick.components import PositionComponent
from roglick.dungeon import features
from roglick.events import MoveEvent,ClimbDownEvent,ClimbUpEvent


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


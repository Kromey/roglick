from roglick.lib import libtcod
from roglick.engine import colors,event
from . import tiles
from roglick.events import MessageEvent


class Tile(object):
    def __init__(self, glyph, name, is_passable=False, is_transparent=None, color_lit=colors.white, color_unlit=colors.dim_gray):
        self._glyph = glyph
        self._name = name
        self._is_passable = is_passable
        if is_transparent is None:
            # By default, impassable Tiles are non-transparent, and vice-versa
            is_transparent = is_passable
        self._is_transparent = is_transparent
        self._color_lit = color_lit
        self._color_unlit = color_unlit

        self._explored = False
        self._feature = None

    @property
    def feature(self):
        return self._feature

    @property
    def explored(self):
        return self._explored

    @property
    def glyph(self):
        if self.feature:
            return self.feature.glyph
        else:
            return self._glyph

    @property
    def name(self):
        if self.feature:
            return self.feature.name
        else:
            return self._name

    @property
    def is_passable(self):
        if self.feature:
            return self.feature.is_passable
        else:
            return self._is_passable

    @property
    def is_transparent(self):
        if self.feature:
            return self.feature.is_transparent
        else:
            return self._is_transparent

    @property
    def color_lit(self):
        if self.feature:
            return self.feature.color_lit
        else:
            return self._color_lit

    @property
    def color_unlit(self):
        if self.feature:
            return self.feature.color_unlit
        else:
            return self._color_unlit

    def explore(self):
        if not self._explored:
            self._explored = True
            if self.feature:
                msg = "You have found a {feature}!".format(
                        feature=self.feature.name)
                event.dispatch(MessageEvent(msg))

    def add_feature(self, feature):
        if isinstance(feature, dict):
            self._feature = Feature(**feature)
        else:
            self._feature = feature

    def __eq__(self, other):
        if isinstance(other, dict):
            return self == self.__class__(**other)
        else:
            return (self.glyph == other.glyph and
                    self.name == other.name and
                    self.is_passable == other.is_passable and
                    self.is_transparent == other.is_transparent and
                    self.color_lit == other.color_lit and
                    self.color_unlit == other.color_unlit)


class Feature(Tile):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)


class Map(object):
    def __init__(self, width, height, random, *args, **kwargs):
        self._width = width
        self._height = height

        self._random = random

        self.make_map(*args, **kwargs)

    def make_map(self, fill=tiles.WallTile):
        self.tiles = [[Tile(**fill) for y in range(self._height)]
                for x in range(self._width)]

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height

    def distance_squared(self, x1, y1, x2, y2):
        return (x1 - x2)**2 + (y1 - y2)**2

    def get_random_cell(self, only_passable=True):
        while True:
            x = self._random.get_int(0, self.width-1)
            y = self._random.get_int(0, self.height-1)

            if not only_passable or self.tiles[x][y].is_passable:
                return x,y

    def create_tunnel(self, x1, y1, x2, y2):
        # Flip a coin to decide if we go horizontal or vertical first
        if self._random.flip_coin():
            self.create_h_tunnel(x1, x2, y1)
            self.create_v_tunnel(y1, y2, x2)
        else:
            self.create_v_tunnel(y1, y2, x1)
            self.create_h_tunnel(x1, x2, y2)

    def create_h_tunnel(self, x1, x2, y):
        for x in range(min(x1, x2), max(x1, x2) + 1):
            self.tiles[x][y] = Tile(**tiles.FloorTile)

    def create_v_tunnel(self, y1, y2, x):
        for y in range(min(y1, y2), max(y1, y2) + 1):
            self.tiles[x][y] = Tile(**tiles.FloorTile)

    def flood_fill(self, start_x, start_y):
        """A generator that yields all passable cells connected to the start.

        Cells are returned as tuples in the form (x,y).
        """
        # We'll need to keep track of what cells we have and have not visited
        # TODO: Better to keep a list of cells, or this double-list of bools?
        visited = [[False for y in range(self.height)]
                for x in range(self.width)]

        # We'll be using a list as a stack to store cells we haven't explored
        cells = []
        # Start the stack with our starting cell
        cells.append((start_x,start_y))

        while 0 < len(cells):
            # Remove the current cell from the stack
            cell = cells.pop()
            # Just a convenience, extract x and y from the cell tuple
            x,y = cell
            # Make sure we haven't been here before
            if visited[x][y]:
                continue

            # Yield this cell before we move on
            yield cell

            # Mark this cell as visited
            visited[x][y] = True

            # Iterate through all neighbors...
            for tx in range(x-1,x+2):
                # ...in all directions
                for ty in range(y-1,y+2):
                    # Don't exceed the map boundaries, of course
                    if tx >=0 and tx < self.width and ty >= 0 and ty < self.height:
                        # Skip over visited cells and walls
                        if not visited[tx][ty] and self.tiles[tx][ty].is_passable:
                            # Whew! After all that, add cell to the stack!
                            cells.append((tx,ty))


class Room(object):
    def __init__(self, x, y, width, height):
        self.x1 = x
        self.y1 = y
        self.x2 = x + width
        self.y2 = y + height

    @property
    def center(self):
        return int((self.x1+self.x2)/2),int((self.y1+self.y2)/2)

    def intersects(self, other):
        # Returns true if this room intersects with another one
        return (self.x1 <= other.x2 and self.x2 >= other.x1 and
                self.y1 <= other.y2 and self.y2 >= other.y1)


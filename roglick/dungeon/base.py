from roglick.engine import random
from roglick.lib import libtcod
from . import tiles


class Tile(object):
    def __init__(self, glyph, is_passable=False, is_transparent=None, color_lit=libtcod.white, color_unlit=libtcod.gray):
        self.glyph = glyph
        self.is_passable = is_passable
        if is_transparent is None:
            # By default, impassable Tiles are non-transparent, and vice-versa
            is_transparent = is_passable
        self.is_transparent = is_transparent
        self.color_lit = color_lit
        self.color_unlit = color_unlit


class Map(object):
    def __init__(self, width, height, fill=tiles.WallTile):
        self._width = width
        self._height = height

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

    def create_tunnel(self, x1, y1, x2, y2):
        # Flip a coin to decide if we go horizontal or vertical first
        if random.get_int(0, 1) == 1:
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

    def intersects(self, other):
        # Returns true if this room intersects with another one
        return (self.x1 <= other.x2 and self.x2 >= other.x1 and
                self.y1 <= other.y2 and self.y2 >= other.y1)


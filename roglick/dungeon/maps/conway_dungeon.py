from roglick.dungeon.base import Map,Room,Tile
from roglick.dungeon import tiles
from roglick.lib import libtcod


class Cave(object):
    def __init__(self):
        self.cells = []

    @property
    def center(self):
        if 0 >= self.size:
            return None

        sum_x = 0
        sum_y = 0
        for cell in self.cells:
            sum_x += cell[0]
            sum_y += cell[1]
        return (int(sum_x/self.size), int(sum_y/self.size))

    @property
    def size(self):
        return len(self.cells)


class ConwayDungeon(Map):
    def __init__(self, width, height, random, *args, **kwargs):
        super().__init__(width, height, random)

        self.make_map(*args, **kwargs)

    def make_map(self, open_prob=45, close_neighbors=4, visits=1, smoothing_passes=2, cave_min_size=10):
        super().make_map()

        self._caves = []
        self._open_cells(open_prob)

        for x in range(int(visits * self.width * self.height)):
            self._visit_random_cell(close_neighbors)

        self._smooth_cave(smoothing_passes)

        self._find_caves(cave_min_size)

        self._connect_caves()

    def _open_cells(self, open_prob):
        for x in range(self.width):
            if x == 0 or x == self.width-1:
                continue
            for y in range(self.height):
                if y == 0 or y == self.height-1:
                    continue
                if self._random.get_int(0,100) < open_prob:
                    self.tiles[x][y] = Tile(**tiles.floor)

    def _visit_random_cell(self, close_neighbors):
        x = self._random.get_int(1, self.width-2)
        y = self._random.get_int(1, self.height-2)

        neighbors = self._count_neighbors(x, y)
        if neighbors > close_neighbors:
            self.tiles[x][y] = Tile(**tiles.wall)
        else:
            self.tiles[x][y] = Tile(**tiles.floor)

    def _smooth_cave(self, smoothing_passes):
        for i in range(smoothing_passes):
            for x in range(self.width):
                if x == 0 or x == self.width-1:
                    continue
                for y in range(self.height):
                    if y == 0 or y == self.height-1:
                        continue
                    if not self.tiles[x][y].is_passable and self._count_orth_neighbors(x, y) <= 1:
                        self.tiles[x][y] = Tile(**tiles.floor)

        for i in range(smoothing_passes):
            for x in range(self.width):
                if x == 0 or x == self.width-1:
                    continue
                for y in range(self.height):
                    if y == 0 or y == self.height-1:
                        continue
                    if self.tiles[x][y].is_passable and self._count_orth_neighbors(x, y) >= 4:
                        self.tiles[x][y] = Tile(**tiles.wall)

    def _find_caves(self, cave_min_size):
        visited = [[False for y in range(self.height)]
                for x in range(self.width)]

        for x in range(self.width):
            for y in range(self.height):
                if visited[x][y]:
                    continue

                if self.tiles[x][y].is_passable:
                    cave = self._map_cave(visited, x, y)

                    if cave.size < cave_min_size:
                        # Too small, fill it in
                        for cx,cy in cave.cells:
                            self.tiles[cx][cy] = Tile(**tiles.wall)
                    else:
                        self._caves.append(cave)
                else:
                    visited[x][y] = True

    def _connect_caves(self):
        while len(self._caves) > 1:
            cave = self._caves.pop()
            cx,cy = cave.center

            # Find the "nearest" cave to this one by comparing centers
            other = self._caves[0]
            ox,oy = other.center
            d2 = self.distance_squared(cx, cy, ox, oy)
            for i in range(1, len(self._caves)):
                ox,oy = self._caves[i].center
                i_d2 = self.distance_squared(cx, cy, ox, oy)
                if i_d2 < d2:
                    other = self._caves[i]
                    d2 = i_d2

            # Found nearest cave, find nearest points
            # Not necessarily actually nearest two points; first we find the
            # point in one cave nearest the other's center, then the point in
            # the other nearest to that one.
            x1,y1 = cave.center
            x2,y2 = other.center
            d2 = self.distance_squared(x1, y1, x2, y2)
            for i_x2,i_y2 in other.cells:
                i_d2 = self.distance_squared(x1, y1, i_x2, i_y2)
                if i_d2 < d2:
                    x2,y2 = i_x2,i_y2
                    d2 = i_d2
            for i_x1,i_y1 in cave.cells:
                i_d2 = self.distance_squared(i_x1, i_y1, x2, y2)
                if i_d2 < d2:
                    x1,y1 = i_x1,i_y1
                    d2 = i_d2

            self.create_tunnel(x1, y1, x2, y2)

    def _count_neighbors(self, x, y):
        neighbors = 0

        for dx in range(-1,2):
            for dy in range(-1,2):
                if dx or dy:
                    tx = x+dx
                    ty = y+dy
                    if tx >=0 and tx < self.width and ty >= 0 and ty < self.height:
                        if not self.tiles[tx][ty].is_passable:
                            neighbors += 1

        return neighbors

    def _count_orth_neighbors(self, x, y):
        neighbors = 0

        for dx in range(-1,2):
            if dx:
                tx = x+dx
                ty = y
                if tx >=0 and tx < self.width and ty >= 0 and ty < self.height:
                    if not self.tiles[tx][ty].is_passable:
                        neighbors += 1

        for dy in range(-1,2):
            if dy:
                tx = x
                ty = y+dy
                if tx >=0 and tx < self.width and ty >= 0 and ty < self.height:
                    if not self.tiles[tx][ty].is_passable:
                        neighbors += 1

        return neighbors

    def _map_cave(self, visited, x, y):
        if visited[x][y] or not self.tiles[x][y].is_passable:
            raise ValueError("Cell ({x},{y}) not valid start for cave".format(
                x=x, y=y))

        cave = Cave()
        for cell in self.flood_fill(x, y):
            cave.cells.append(cell)
            x,y = cell
            visited[x][y] = True

        return cave



from roglick.dungeon.base import Map,Room,Tile
from roglick.dungeon import tiles
from roglick.engine import random
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
    def __init__(self, width, height, open_prob=45, close_neighbors=4, visits=1, smoothing_passes=2, cave_min_size=10):
        super().__init__(width, height)

        self._caves = []
        self.make_map(open_prob, close_neighbors, visits, smoothing_passes, cave_min_size)

    def make_map(self, open_prob, close_neighbors, visits, smoothing_passes, cave_min_size):
        self._open_cells(open_prob)

        for x in range(int(visits * self.width * self.height)):
            self._visit_random_cell(close_neighbors)

        self._smooth_cave(smoothing_passes)

        self._find_caves(cave_min_size)
        for cave in self._caves:
            x,y = cave.center
            self.tiles[x][y].color_lit = libtcod.white

    def _open_cells(self, open_prob):
        for x in range(self.width):
            if x == 0 or x == self.width-1:
                continue
            for y in range(self.height):
                if y == 0 or y == self.height-1:
                    continue
                if random.get_int(0,100) < open_prob:
                    self.tiles[x][y] = Tile(**tiles.FloorTile)

    def _visit_random_cell(self, close_neighbors):
        x = random.get_int(1, self.width-2)
        y = random.get_int(1, self.height-2)

        neighbors = self._count_neighbors(x, y)
        if neighbors > close_neighbors:
            self.tiles[x][y] = Tile(**tiles.WallTile)
        else:
            self.tiles[x][y] = Tile(**tiles.FloorTile)

    def _smooth_cave(self, smoothing_passes):
        for i in range(smoothing_passes):
            for x in range(self.width):
                if x == 0 or x == self.width-1:
                    continue
                for y in range(self.height):
                    if y == 0 or y == self.height-1:
                        continue
                    if not self.tiles[x][y].is_passable and self._count_orth_neighbors(x, y) <= 1:
                        self.tiles[x][y] = Tile(**tiles.FloorTile)

        for i in range(smoothing_passes):
            for x in range(self.width):
                if x == 0 or x == self.width-1:
                    continue
                for y in range(self.height):
                    if y == 0 or y == self.height-1:
                        continue
                    if self.tiles[x][y].is_passable and self._count_orth_neighbors(x, y) >= 4:
                        self.tiles[x][y] = Tile(**tiles.WallTile)

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
                            self.tiles[cx][cy] = Tile(**tiles.WallTile)
                            self.tiles[cx][cy].color_lit = libtcod.purple
                    else:
                        self._caves.append(cave)
                else:
                    visited[x][y] = True
                    self.tiles[x][y].color_lit = libtcod.red

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
            self.tiles[x][y].color_lit = libtcod.green

        return cave



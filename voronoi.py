import time


from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D, smootherstep, smoothstep, lerp
from roglick.utils import clamp
from roglick.engine import random,colors

width=180
height=100
font='data/fonts/arial10x10.png'

libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(width, height, "Voronoi Diagram Test".encode('UTF-8'), False)


def init_terrain():
    #terrain = []
    #for x in range(width):
    #    terrain.append([(None,width*width+height*height) for y in range(height)])
    terrain = [[None for y in range(height)] for x in range(width)]

    return terrain


def draw_graph(terrain, cell_color=False, with_screenshot=False):
    for x in range(width):
        for y in range(height):
            if terrain[x][y] is None:
                libtcod.console_put_char_ex(0,
                        x, y,
                        b'X', libtcod.red, libtcod.white)
                continue

            if terrain[x][y].pos == (x,y):
                c = b'#'
            else:
                c = b' '

            if not cell_color or terrain[x][y].color is None:
                color = int(16777216 * terrain[x][y].cell_id/points)
                color = libtcod.Color(color & 255, (color >> 8) & 255, (color >> 16) & 255)
            else:
                color = terrain[x][y].color

            libtcod.console_put_char_ex(0,
                    x, y,
                    c, libtcod.red, color)

    libtcod.console_flush()
    if with_screenshot:
        libtcod.sys_save_screenshot()


def add_voronoi_cell(terrain, cell):
    px,py = cell.pos
    terrain[px][py] = cell

    for d in range(1, max(width,height)):
        changed = False
        for x in range(px-d, px+d+1):
            if x < 0 or x >= width:
                continue
            dist2 = cell.dist2_to(x, py-d)
            if py-d >= 0 and (terrain[x][py-d] is None or dist2 <= terrain[x][py-d].dist2_to(x,py-d)):
                terrain[x][py-d] = cell
                changed = True
            if py+d < height and (terrain[x][py+d] is None or dist2 <= terrain[x][py+d].dist2_to(x,py+d)):
                terrain[x][py+d] = cell
                changed = True

        for y in range(py-d, py+d+1):
            if y < 0 or y >= height:
                continue
            dist2 = cell.dist2_to(px-d, y)
            if px-d >= 0 and (terrain[px-d][y] is None or dist2 <= terrain[px-d][y].dist2_to(px-d,y)):
                terrain[px-d][y] = cell
                changed = True
            if px+d < width and (terrain[px+d][y] is None or dist2 <= terrain[px+d][y].dist2_to(px+d,y)):
                terrain[px+d][y] = cell
                changed = True
        if not changed:
            break


class VorCell(object):
    next_cell_id = 0
    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.color = None

        self.cell_id = VorCell.next_cell_id
        VorCell.next_cell_id += 1

        self.clear_cache()

    def clear_cache(self):
        self._left_neighbors = None
        self._right_neighbors = None

    def dist2_to(self, x, y):
        return (x - self.x)**2 + (y - self.y)**2

    @property
    def pos(self):
        return (self.x, self.y)

    @property
    def left_neighbors(self):
        if self._left_neighbors is None:
            self._count_neighbors()

        return self._left_neighbors

    @property
    def right_neighbors(self):
        if self._right_neighbors is None:
            self._count_neighbors()

        return self._right_neighbors

    def _count_neighbors(self):
        neighbors = 0
        cur_cell = -1
        for x in range(width):
            if terrain[x][self.y] is None:
                continue

            if terrain[x][self.y].cell_id != cur_cell:
                if terrain[x][self.y] == self:
                    self._left_neighbors = neighbors

                neighbors += 1
                cur_cell = terrain[x][self.y].cell_id

        self._right_neighbors = neighbors - self._left_neighbors

    def __repr__(self):
        return "VorCell({},{})".format(self.x, self.y)


terrain = init_terrain()
points = 200
cells = [VorCell(random.get_int(0, width-1), random.get_int(0, height-1)) for i in range(points)]
for cell in cells:
    add_voronoi_cell(terrain, cell)

draw_graph(terrain)

# Lloyd relaxation
for i in range(2):
    weights = [[0,0,0] for i in range(points)]
    for x in range(width):
        for y in range(height):
            cell = terrain[x][y].cell_id
            weights[cell][0] += x
            weights[cell][1] += y
            weights[cell][2] += 1

    for cell in range(points):
        if weights[cell][2] == 0:
            continue

        x_avg = weights[cell][0] / weights[cell][2]
        y_avg = weights[cell][1] / weights[cell][2]
        cells[cell].x = round(x_avg)
        cells[cell].y = round(y_avg)

    for cell in cells:
        add_voronoi_cell(terrain, cell)

    #time.sleep(2)

    draw_graph(terrain)


#ocean_terrain = []
#mount_terrain = []
#for sx,sy in centers:
#    # Walk from current position to left edge, counting terrain we find
#    cur_cell = terrain[sx][sy][0]
#    cell_count = 1
#    for x in range(sx-1, -1, -1):
#        if terrain[x][sy][0] != cur_cell:
#            cell_count += 1
#            cur_cell = terrain[x][sy][0]
#
#    if cell_count <= 2:
#        ocean_terrain.append(terrain[sx][sy][0])
#    else:
#        cur_cell = terrain[sx][sy][0]
#        cell_count = 1
#        for x in range(sx, width):
#            if terrain[x][sy][0] != cur_cell:
#                cell_count += 1
#                cur_cell = terrain[x][sy][0]
#
#        if cell_count == 2:
#            mount_terrain.append(terrain[sx][sy][0])
for cell in cells:
    if cell.left_neighbors <= 2:
        cell.color = libtcod.blue
    elif cell.right_neighbors == 2:
        cell.color = libtcod.silver
    else:
        cell.color = libtcod.light_green

draw_graph(terrain, True)

# Heightmap
for cell in cells:
    if cell.color == libtcod.light_green:
        d = smoothstep(0, cell.left_neighbors+cell.right_neighbors-2, cell.left_neighbors-2)
        color = colors.HSVBlendedColor(colors.black, colors.white, d)
        cell.color = color

draw_graph(terrain, True)

while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_SPACE:
        break
exit()


print(mount_terrain)
cell_colors = [None for x in centers]
for y in range(height):
    coast_x = 0
    for x in range(width):
        if terrain[x][y][1] == 0:
            c = b'#'
        else:
            c = b' '
            #c = str(terrain[x][y][0])[-1].encode('UTF-8')

        if terrain[x][y][0] in ocean_terrain:
            color = libtcod.blue
            coast_x = x
        elif terrain[x][y][0] in mount_terrain:
            color = libtcod.silver
        else:
            cur_cell = terrain[x][y][0]
            shore_distance = 0
            mount_distance = 0
            sx,sy = centers[cur_cell]
            if cell_colors[cur_cell] is None:
                for wx in range(sx, -1, -1):
                    if terrain[wx][y][0] in ocean_terrain:
                        break
                    if cur_cell != terrain[wx][y][0]:
                        shore_distance += 1
                        cur_cell = terrain[wx][y][0]
                cur_cell = terrain[x][y][0]
                for wx in range(sx, width):
                    if terrain[wx][y][0] in mount_terrain:
                        break
                    if cur_cell != terrain[wx][y][0]:
                        mount_distance += 1
                        cur_cell = terrain[wx][y][0]
                d = smoothstep(0, shore_distance+mount_distance, shore_distance)
                print(terrain[x][y][0], shore_distance, mount_distance, d)
                color = colors.HSVBlendedColor(colors.black, colors.white, d)
                cell_colors[terrain[x][y][0]] = color
            #d = 0
            #for peak in mount_terrain:
            #    d += smoothstep(0, (centers[peak][0]-x)**2+(centers[peak][1]-y)**2, (x-coast_x)**2)
            #d /= len(mount_terrain)
            #color = colors.HSVBlendedColor(colors.black, colors.white, d**2)
            color = cell_colors[terrain[x][y][0]]

        libtcod.console_put_char_ex(0,
                x, y,
                c, libtcod.black, color)

libtcod.console_set_default_foreground(0, libtcod.red)
for i in range(len(centers)):
    sx,sy = centers[i]
    libtcod.console_print(0, sx-1, sy+1, str(i).encode('UTF-8'))

libtcod.console_flush()
#libtcod.sys_save_screenshot()

while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_SPACE:
        break


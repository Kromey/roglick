import time


from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D, smootherstep, smoothstep, lerp
from roglick.utils import clamp
from roglick.engine import random

width=180
height=100
font='data/fonts/arial10x10.png'

libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(width, height, "Voronoi Diagram Test".encode('UTF-8'), False)


def init_cells():
    cells = []
    for x in range(width):
        cells.append([(None,width*width+height*height) for y in range(height)])

    return cells


def add_voronoi_cell(cells, cell_id, x, y):
    px,py = x,y
    cells[px][py] = (cell_id, 0)

    for d in range(1, max(width,height)):
        changed = False
        for x in range(px-d, px+d+1):
            if x < 0 or x >= width:
                continue
            dist2 = (px - x)**2 + (d)**2
            if py-d >= 0 and dist2 < cells[x][py-d][1]:
                cells[x][py-d] = (cell_id, dist2)
                changed = True
            if py+d < height and dist2 < cells[x][py+d][1]:
                cells[x][py+d] = (cell_id, dist2)
                changed = True

        for y in range(py-d, py+d+1):
            if y < 0 or y >= height:
                continue
            dist2 = (py - y)**2 + (d)**2
            if px-d >= 0 and dist2 < cells[px-d][y][1]:
                cells[px-d][y] = (cell_id, dist2)
                changed = True
            if px+d < width and dist2 < cells[px+d][y][1]:
                cells[px+d][y] = (cell_id, dist2)
                changed = True
        if not changed:
            break


cells = init_cells()
points = 200
centers = []
for pi in range(points):
    px = random.get_int(0, width-1)
    py = random.get_int(0, height-1)
    centers.append((px,py))

    add_voronoi_cell(cells, pi, px, py)

for i in range(5):
    weights = [[0,0,0] for i in range(points)]
    for x in range(width):
        for y in range(height):
            cell = cells[x][y][0]
            weights[cell][0] += x
            weights[cell][1] += y
            weights[cell][2] += 1

    for i in range(points):
        x_avg = weights[i][0] / weights[i][2]
        y_avg = weights[i][1] / weights[i][2]
        centers[i] = (int(x_avg),int(y_avg))

    cells = init_cells()
    for i in range(points):
        add_voronoi_cell(cells, i, centers[i][0], centers[i][1])


    for x in range(width):
        for y in range(height):
            if cells[x][y][1] == 0:
                c = b'#'
            else:
                c = b' '
            color = int(16777216 * cells[x][y][0]/points)
            color = libtcod.Color(color & 255, (color >> 8) & 255, (color >> 16) & 255)

            libtcod.console_put_char_ex(0,
                    x, y,
                    c, libtcod.light_green, color)

    libtcod.console_flush()
    libtcod.sys_save_screenshot()


ocean_cells = []
mount_cells = []
for sx,sy in centers:
    # Walk from current position to left edge, counting cells we find
    cur_cell = cells[sx][sy][0]
    cell_count = 1
    for x in range(sx-1, -1, -1):
        if cells[x][sy][0] != cur_cell:
            cell_count += 1
            cur_cell = cells[x][sy][0]

    if cell_count <= 2:
        ocean_cells.append(cells[sx][sy][0])
    else:
        cur_cell = cells[sx][sy][0]
        cell_count = 1
        for x in range(sx, width):
            if cells[x][sy][0] != cur_cell:
                cell_count += 1
                cur_cell = cells[x][sy][0]

        if cell_count == 2:
            mount_cells.append(cells[sx][sy][0])


for x in range(width):
    for y in range(height):
        if cells[x][y][1] == 0:
            c = b'#'
        else:
            c = b' '

        if cells[x][y][0] in ocean_cells:
            color = libtcod.blue
        elif cells[x][y][0] in mount_cells:
            color = libtcod.silver
        else:
            color = libtcod.light_green

        libtcod.console_put_char_ex(0,
                x, y,
                c, libtcod.black, color)

libtcod.console_flush()
libtcod.sys_save_screenshot()

while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_SPACE:
        break


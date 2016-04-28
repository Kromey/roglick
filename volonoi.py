from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D, smootherstep, smoothstep, lerp
from roglick.utils import clamp
from roglick.engine import random

width=180
height=100
font='data/fonts/arial10x10.png'

libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(width, height, "Perlin Noise Test".encode('UTF-8'), False)


cells = []
for x in range(width):
    cells.append([(0,width*width+height*height) for y in range(height)])

points = 200
for pi in range(points):
    px = random.get_int(0, width-1)
    py = random.get_int(0, height-1)

    cell, dist = cells[px][py]
    cells[px][py] = (pi, 0)

    for d in range(1, max(width,height)):
        changed = False
        for x in range(px-d, px+d+1):
            if x < 0 or x >= width:
                continue
            dist2 = (px - x)**2 + (d)**2
            if py-d >= 0 and dist2 < cells[x][py-d][1]:
                cells[x][py-d] = (pi, dist2)
                changed = True
            if py+d < height and dist2 < cells[x][py+d][1]:
                cells[x][py+d] = (pi, dist2)
                changed = True

        for y in range(py-d, py+d+1):
            if y < 0 or y >= height:
                continue
            dist2 = (py - y)**2 + (d)**2
            if px-d >= 0 and dist2 < cells[px-d][y][1]:
                cells[px-d][y] = (pi, dist2)
                changed = True
            if px+d < width and dist2 < cells[px+d][y][1]:
                cells[px+d][y] = (pi, dist2)
                changed = True
        if not changed:
            break

for x in range(width):
    for y in range(height):
        if cells[x][y][1] == 0:
            c = b'#'
        else:
            c = b' '
        color = int(255 * cells[x][y][0]/points)
        color = libtcod.Color(color,color,color)

        libtcod.console_put_char_ex(0,
                x, y,
                c, libtcod.light_green, color)

libtcod.console_flush()
while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_SPACE:
        break


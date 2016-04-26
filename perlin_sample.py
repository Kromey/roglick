from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D

width=180
height=100
font='data/fonts/arial10x10.png'

libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(width, height, "Perlin Noise Test".encode('UTF-8'), False)

x_scale = 256 / width
y_scale = 256 / height

perlin = PerlinNoise2D()

for x in range(width):
    sx = x * x_scale
    for y in range(height):
        sy = y * y_scale
        p = perlin.octave(sx, sy)
        color = int(256 * p)
        print(x, y, sx, sy, p, color)
        libtcod.console_put_char_ex(0,
                x, y,
                b' ', libtcod.white, libtcod.Color(color,color,color))

libtcod.console_flush()

key = libtcod.console_wait_for_keypress(True)


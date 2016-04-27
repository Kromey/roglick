from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D, smootherstep, smoothstep
from roglick.utils import clamp

width=180
height=100
font='data/fonts/arial10x10.png'

libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(width, height, "Perlin Noise Test".encode('UTF-8'), False)

x_scale = 0.211 #256 / width
y_scale = 0.211 #256 / height

x_offset = 0.777
y_offset = 0.777

print("Initializing Perlin Noise...")
perlin = PerlinNoise2D()
print("Done!")

min_p = 256
max_p = -256

ocean = libtcod.Color(0,0,255)
beach = libtcod.Color(217,160,102)
grass = libtcod.Color(143,151,74)
woods = libtcod.Color(55,148,110)
mount = libtcod.Color(132,126,135)
snow  = libtcod.Color(255,255,255)
def color_map(p):
    if p <= 0.1:
        return ocean
    elif p <= 0.2:
        return beach
    elif p <= 0.5:
        return grass
    elif p <= 0.7:
        return woods
    elif p <= 0.85:
        return mount
    else:
        return snow

print("Generating Noise...")
for x in range(width):
    sx = x * x_scale + x_offset
    grad = smoothstep(0.0, 1.0, x/width) * 5
    for y in range(height):
        sy = y * y_scale + y_offset
        p = clamp((grad - perlin.octave(sx, sy, 7, 0.25)) / 5, 0.0, 1.0)
        min_p = min(min_p, p)
        max_p = max(max_p, p)
        color = color_map(p)
        #print(x, y, sx, sy, p, color)
        libtcod.console_put_char_ex(0,
                x, y,
                b' ', libtcod.white, color)
print("Done!")

libtcod.console_flush()

while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_ENTER:
        break

print(min_p, max_p)


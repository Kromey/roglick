from roglick.lib import libtcod
from roglick.dungeon.utils import PerlinNoise2D, smootherstep, smoothstep, lerp
from roglick.utils import clamp
from roglick.engine import random

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
    elif p <= 0.8:
        return woods
    elif p <= 0.98:
        return mount
    else:
        return snow

# Lines for our gradient peaks
low_x1 = low_x2 = random.get_int(1,15)
while low_x1 == low_x2 or low_x2 <= 0:
    low_x2 = low_x1 + random.get_int(-9,9)*3
#hi_x1 = hi_x2 = width-random.get_int(1,25)
#while hi_x1 == hi_x2 or hi_x2 >= width:
#    hi_x2 += random.get_int(-4,4)*3
hi_x1 = width - low_x2
hi_x2 = width - low_x1

# Calculate slopes
lo_m = (width)/(low_x2 - low_x1)
hi_m = (width)/(hi_x2 - hi_x1)

# Now calculate y-intercept
lo_b = -(lo_m * low_x1)
hi_b = -(hi_m * hi_x1)

print("Lo: y={m}x + {b}".format(m=lo_m, b=lo_b))
print("Hi: y={m}x + {b}".format(m=hi_m, b=hi_b))

print("Generating Noise...")
for x in range(width):
    sx = x * x_scale + x_offset
    for y in range(height):
        sy = y * y_scale + y_offset
        #grad = smoothstep(0.0, 1.0, (x - (y - lo_b)/lo_m)/((y - hi_b)/hi_m)) * 5
        low = (y - lo_b)/lo_m
        high = (y - hi_b)/hi_m
        if x <= high:
            grad = smoothstep(low, high, x)
        else:
            grad = smoothstep(low, high, (2*high-x))
        p = clamp(grad - perlin.octave(sx, sy, 7, 0.25)/3, 0.0, 1.0)
        #p = grad
        min_p = min(min_p, p)
        max_p = max(max_p, p)
        color = color_map(p)
        #color = libtcod.Color(int(p*255), int(p*255), int(p*255))
        #print(x, y, sx, sy, p, color)
        if x == 0:
            print(y, low, high, grad, p)
        libtcod.console_put_char_ex(0,
                x, y,
                b' ', libtcod.white, color)
print("Done!")

libtcod.console_flush()

while True:
    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_SPACE:
        break

print(min_p, max_p)


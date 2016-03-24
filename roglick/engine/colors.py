from roglick.lib import libtcod

class Color(object):
    def __init__(self, r, g, b):
        self._rgb = (r,g,b)
        self._libtcod = None

    @property
    def libtcod(self):
        if self._libtcod is None:
            self._libtcod = libtcod.Color(*self._rgb)

        return self._libtcod

def RGBtoHSV(r, g, b):
    # If we were given black, return black
    if r == 0 and g == 0 and b == 0:
        return 0,0,0

    # We need RGB from 0-1, not 0-255
    r /= 255
    g /= 255
    b /= 255

    min_rgb = min(r, g, b)
    max_rgb = max(r, g, b)
    delta = max_rgb - min_rgb

    v = max_rgb
    s = delta / max_rgb

    if delta == 0:
        return 0,s,v
    elif r == max_rgb:
        # Between yellow and magenta
        h = (g - b) / delta
    elif g == max_rgb:
        # Between cyan and yellow
        h = 2 + (b - r) / delta
    else:
        # Between magenta and cyan
        h = 4 + (r - g) / delta

    h *= 60 # Degrees
    if h < 0:
        h += 360

    return h,s,v

# This color palette is taken from the "DB32" palette
# http://pixeljoint.com/forum/forum_posts.asp?TID=16247
black = Color(0,0,0)
valhalla = Color(34,32,52)
loulou = Color(69,40,60)
oiled_cedar = Color(102,57,49)
rope = Color(143,86,59)
orange = Color(223,113,38)
twine = Color(217,160,102)
pancho = Color(238,195,154)
gold = Color(251,242,54)
atlantis = Color(153,229,80)
christi = Color(106,190,48)
elf_green = Color(55,148,110)
dell = Color(75,105,47)
verdigris = Color(82,75,36)
opal = Color(50,60,57)
deep_koamaru = Color(63,63,116)
venice_blue = Color(48,96,130)
royal_blue = Color(91,110,225)
cornflower = Color(99,155,255)
viking = Color(95,205,228)
light_steel_blue = Color(203,219,252)
white = Color(255,255,255)
heather = Color(155,173,183)
topaz = Color(132,126,135)
dim_gray = Color(105,106,106)
smokey_ash = Color(89,86,82)
clairvoyant = Color(118,66,138)
red = Color(172,50,50)
mandy = Color(217,87,99)
plum = Color(215,123,186)
rain_forest = Color(143,151,74)
stinger = Color(138,111,48)


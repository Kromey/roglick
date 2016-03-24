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

class RGBBlendedColor(Color):
    def __init__(self, color1, color2, blend=0.50):
        # Get the RGB components of our base colors
        r1,g1,b1 = color1._rgb
        r2,g2,b2 = color2._rgb

        # Easy-peasy: linearly interpolate each component...
        r = r1 + (r2 - r1) * blend
        g = g1 + (g2 - g1) * blend
        b = b1 + (b2 - b1) * blend

        # ...and put them all back together into our new color
        super().__init__(r,g,b)

class HSVBlendedColor(Color):
    def __init__(self, color1, color2, blend=0.50):
        # Convert our base colors to HSV
        h1,s1,v1 = RGBtoHSV(*color1._rgb)
        h2,s2,v2 = RGBtoHSV(*color2._rgb)

        # Linearly interpolate s and v
        s = s1 + (s2 - s1) * blend
        v = v1 + (v2 - v1) * blend

        # h gets tricky because it's the angle around a circle...
        # Logic here is taken from:
        # http://www.stuartdenman.com/improved-color-blending/
        hmin = min(h1, h2)
        hmax = max(h1, h2)
        d = hmax - hmin
        if hmax == h1:
            blend = 1 - blend
        if d > 180:
            hmin = hmin + 360
            h = (hmin + blend * (hmax-hmin)) % 360
        else:
            h = hmin + blend * d

        # Now convert back to RGB and create the Color
        super().__init__(*HSVtoRGB(h,s,v))

def RGBtoHSV(r, g, b):
    """Convert RGB values to HSV

    Algorithm is taken from https://www.cs.rit.edu/~ncs/color/t_convert.html
    """
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


def HSVtoRGB(h, s, v):
    """Convert HSV values to RGB

    Algorithm is taken from https://www.cs.rit.edu/~ncs/color/t_convert.html
    """
    if s == 0:
        # Achromatic, i.e. gray
        gray = v * 255
        return gray,gray,gray

    # Calculate our "sectors"
    h /= 60
    i = int(h)
    # A few intermediate values we may need
    f = h - i
    p = v * (1 - s)
    q = v * (1 - s * f)
    t = v * (1 - s * (1 - f))

    # Figure out which "sector" of the HSV cylinder we're in and assign RGB
    if i == 0:
        r = v
        g = t
        b = p
    elif i == 1:
        r = q
        g = v
        b = p
    elif i == 2:
        r = p
        g = v
        b = t
    elif i == 3:
        r = p
        g = q
        b = v
    elif i == 4:
        r = t
        g = p
        b = v
    else:
        r = v
        g = p
        b = q

    r *= 255
    g *= 255
    b *= 255

    return r,g,b

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


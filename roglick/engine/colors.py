from roglick.lib import libtcod

class RGBBlendedColor(libtcod.Color):
    def __init__(self, color1, color2, blend=0.50):
        # Get the RGB components of our base colors
        r1,g1,b1 = color1.r,color1.g,color1.b
        r2,g2,b2 = color2.r,color2.g,color2.b

        # Easy-peasy: linearly interpolate each component...
        r = r1 + (r2 - r1) * blend
        g = g1 + (g2 - g1) * blend
        b = b1 + (b2 - b1) * blend

        # ...and put them all back together into our new color
        super().__init__(int(r),int(g),int(b))

class HSVBlendedColor(libtcod.Color):
    def __init__(self, color1, color2, blend=0.50):
        # Get the HSV components of our base colors
        h1,s1,v1 = RGBtoHSV(color1.r,color1.g,color1.b)
        h2,s2,v2 = RGBtoHSV(color2.r,color2.g,color2.b)

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
        r,g,b = HSVtoRGB(h,s,v)
        super().__init__(int(r),int(g),int(b))

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
black = libtcod.Color(0,0,0)
valhalla = libtcod.Color(34,32,52)
loulou = libtcod.Color(69,40,60)
oiled_cedar = libtcod.Color(102,57,49)
rope = libtcod.Color(143,86,59)
orange = libtcod.Color(223,113,38)
twine = libtcod.Color(217,160,102)
pancho = libtcod.Color(238,195,154)
gold = libtcod.Color(251,242,54)
atlantis = libtcod.Color(153,229,80)
christi = libtcod.Color(106,190,48)
elf_green = libtcod.Color(55,148,110)
dell = libtcod.Color(75,105,47)
verdigris = libtcod.Color(82,75,36)
opal = libtcod.Color(50,60,57)
deep_koamaru = libtcod.Color(63,63,116)
venice_blue = libtcod.Color(48,96,130)
royal_blue = libtcod.Color(91,110,225)
cornflower = libtcod.Color(99,155,255)
viking = libtcod.Color(95,205,228)
light_steel_blue = libtcod.Color(203,219,252)
white = libtcod.Color(255,255,255)
heather = libtcod.Color(155,173,183)
topaz = libtcod.Color(132,126,135)
dim_gray = libtcod.Color(105,106,106)
smokey_ash = libtcod.Color(89,86,82)
clairvoyant = libtcod.Color(118,66,138)
red = libtcod.Color(172,50,50)
mandy = libtcod.Color(217,87,99)
plum = libtcod.Color(215,123,186)
rain_forest = libtcod.Color(143,151,74)
stinger = libtcod.Color(138,111,48)


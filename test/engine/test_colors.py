from roglick.engine import colors


def test_rgb_conversion():
    for rgb,hsv in get_color_fields():
        h,s,v = colors.RGBtoHSV(*rgb)

        # Need to round our percentages for comparison
        s = round(s, 2)
        v = round(v, 2)

        assert hsv == (h,s,v)

def test_hsv_conversion():
    for rgb,hsv in get_color_fields():
        r,g,b = colors.HSVtoRGB(*hsv)

        # Need to round our results for comparison
        r = round(r)
        g = round(g)
        b = round(b)

        assert rgb == (r,g,b)

def get_color_fields():
    """A generator of equivalent RGB,HSV tuples.

    This generator yields a sequence of items in the form:
        (r,g,b), (h,s,v)
    The two tuples represent the same color, the first in the RGB space and the
    second in the HSV space.

    This set of data is pulled from the "RGB to HSV color table" at
    http://www.rapidtables.com/convert/color/rgb-to-hsv.htm
    """
    yield (0,0,0), (0,0,0)
    yield (255,255,255), (0,0,1.00)
    yield (255,0,0), (0,1.00,1.00)
    yield (0,255,0), (120,1.00,1.00)
    yield (0,0,255), (240,1.00,1.00)
    yield (255,255,0), (60,1.00,1.00)
    yield (0,255,255), (180,1.00,1.00)
    yield (255,0,255), (300,1.00,1.00)
    yield (191,191,191), (0,0,0.75)
    yield (128,128,128), (0,0,0.50)
    yield (128,0,0), (0,1.00,0.50)
    yield (128,128,0), (60,1.00,0.50)
    yield (0,128,0), (120,1.00,0.50)
    yield (128,0,128), (300,1.00,0.50)
    yield (0,128,128), (180,1.00,0.50)
    yield (0,0,128), (240,1.00,0.50)


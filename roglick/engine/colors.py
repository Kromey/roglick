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

white = Color(255,255,255)
black = Color(0,0,0)
gray = Color(127,127,127)


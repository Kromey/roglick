from roglick.lib import libtcod


class Random(object):
    def __init__(self, seed=None, generator=None):
        if generator is not None:
            self._gen = generator
        elif seed is None:
            self._gen = libtcod.random_new()
        else:
            self._gen = libtcod.random_new_from_seed(seed)

    @property
    def generator(self):
        return self._gen

    def get_int(self, min=None, max=None):
        if min is None and max is None:
            min = 0
            max = 2147483647
        elif max is None:
            # This weird case is if called with a single positional argument;
            # assume the intention was to get a value between 0 and that.
            max = min
            min = 0
        elif min is None:
            min = 0

        return libtcod.random_get_int(self._gen, min, max)

    def flip_coin(self):
        return libtcod.random_get_int(self._gen, 0, 1)

    def roll_dice(self, num=1, sides=6):
        total = 0

        for x in range(num):
            total += self.get_int(1, sides)

        return total


_default = Random(generator=0)

def get_int(min=None, max=None):
    return _default.get_int(min, max)

def flip_coin():
    return _default.flip_coin()

def roll_dice(num=1, sides=6):
    return _default.roll_dice(num, sides)


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
        return self.one_in(2)

    def roll_dice(self, num=1, sides=6):
        total = 0

        for x in range(num):
            total += self.get_int(1, sides)

        return total

    def one_in(self, odds):
        return self.get_int(1, odds) == 1

    def probability(self, prob):
        if prob < 1:
            # Assume we were given percentage in the range 0-1
            prob = int(prob * 100)

        return self.get_int(max=99) < prob

    def choice(self, choices):
        i = self.get_int(0, len(choices)-1)
        return choices[i]

    def shuffle(self, deck):
        """Randomly rearrange a list using a Fisher-Yates shuffle.

        This version of the algorithm, re-implemented for computer use, first
        conceived by Richard Durstenfeld and popularized by Donald E. Knuth.
        """
        for i in range(len(deck)-1, 0, -1):
            j = self.get_int(0, i)
            deck[i], deck[j] = deck[j], deck[i]


_default = Random(generator=0)

def get_int(*args, **kwargs):
    return _default.get_int(*args, **kwargs)

def flip_coin():
    return _default.flip_coin()

def roll_dice(*args, **kwargs):
    return _default.roll_dice(*args, **kwargs)

def one_in(*args, **kwargs):
    return _default.one_in(*args, **kwargs)

def probability(*args, **kwargs):
    return _default.probability(*args, **kwargs)

def choice(*args, **kwargs):
    return _default.choice(*args, **kwargs)

def shuffle(*args, **kwargs):
    return _default.shuffle(*args, **kwargs)


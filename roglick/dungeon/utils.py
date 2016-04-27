from roglick.engine import random
from roglick.utils import clamp


def smoothstep(a, b, x):
    """Basic S-curve interpolation function.

    Based on reference implementation available at
    https://en.wikipedia.org/wiki/Smoothstep
    """
    x = clamp((x - a)/(b - a), 0.0, 1.0)
    return x*x*(3 - 2*x)

def smootherstep(a, b, x):
    """Improved S-curve interpolation function.

    Based on reference implementation of the improved algorithm proposed by
    Ken Perlin that is available at https://en.wikipedia.org/wiki/Smoothstep
    """
    x = clamp((x - a)/(b - a), 0.0, 1.0)
    return x*x*x*(x*(x*6 - 15) + 10);

def lerp(a, b, x):
    """Linear interpolation function."""
    return a + x * (b - a)


class PerlinNoise2D(object):
    def __init__(self, seed=None):
        self.p = [x for x in range(256)]

        if seed is None:
            seed = random.get_int()

        rand = random.Random(seed)
        rand.shuffle(self.p)

    def octave(self, x, y, octaves=5, persistence=0.5):
        total = 0
        frequency = 1
        amplitude = 1
        max_val = 0

        for i in range(octaves):
            total += self.noise(x*frequency, y*frequency) * amplitude

            max_val += amplitude

            amplitude *= persistence
            frequency *= 2

        return total / max_val

    def noise(self, x, y):
        xi = int(x)
        yi = int(y)

        xf = x - xi
        yf = y - yi
        u = self.fade(xf)
        v = self.fade(yf)

        aa = self.p_hash(self.p_hash( xi )+  yi )
        ab = self.p_hash(self.p_hash( xi )+ yi+1)
        ba = self.p_hash(self.p_hash(xi+1)+  yi )
        bb = self.p_hash(self.p_hash(xi+1)+ yi+1)

        x1 = lerp(self.grad(aa, xf , yf), self.grad(ba, xf-1, yf), u)
        x2 = lerp(self.grad(ab, xf , yf-1), self.grad(bb, xf-1, yf-1), u)

        return (lerp(x1, x2, v) + 1) / 2 # Constrain to [0,1] rather than [-1,1]

    def fade(self, t):
        return smootherstep(0.0, 1.0, t)

    def p_hash(self, i):
        i = i & 255
        return self.p[i]

    def grad(self, h, x, y):
        """This gradient function is based on Riven's optimization

        Source: http://riven8192.blogspot.com/2010/08/calculate-perlinnoise-twice-as-fast.html
        """
        h = h % 4

        if h == 0:
            return x + y
        elif h == 1:
            return -x + y
        elif h == 2:
            return x - y
        elif h == 3:
            return -x - y
        else:
            # Never happens
            return 0


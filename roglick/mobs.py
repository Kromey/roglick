import json
from glob import glob


from roglick.engine import colors


class Mob(object):
    pass

npcs = Mob()

for mfile in glob('data/mobs/*.json'):
    with open(mfile) as fh:
        mob = json.load(fh)

    name = mob['name'].lower().replace(' ', '_')
    mob['color'] = getattr(colors, mob['color'])
    setattr(npcs, name, mob)


import json


from roglick.engine import colors


class Terrain(object):
    pass

tiles = Terrain()
features = Terrain()

with open('data/terrain.json') as fh:
    terrain = json.load(fh)

for tile in terrain['tiles']:
    name = tile['name'].lower().replace(' ', '_')
    tile['color'] = getattr(colors, tile['color'])
    setattr(tiles, name, tile)

for feature in terrain['features']:
    name = feature['name'].lower().replace(' ', '_')
    feature['color'] = getattr(colors, feature['color'])
    setattr(features, name, feature)


from .base import Map,Tile,Feature


from roglick.engine import colors,file_obj


class Terrain(file_obj.FileObj):
    def __init__(self, key):
        super().__init__('data/terrain.json', key)

    def _process_item(self, item):
        item['color'] = getattr(colors, item['color'])
        return super()._process_item(item)


tiles = Terrain('tiles')
features = Terrain('features')


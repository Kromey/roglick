from roglick.engine import colors,file_obj


class Mob(file_obj.MultiFileObj):
    def __init__(self):
        super().__init__('data/mobs/*.json')

    def _process_item(self, item):
        item['sprite']['color'] = getattr(colors, item['sprite']['color'])
        return super()._process_item(item)


npcs = Mob()


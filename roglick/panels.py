from roglick.components import PositionComponent,SpriteComponent
from roglick.engine import panels


# Define our panel contexts
panels.PanelContext.MapScreen = 'map'


class MapPanel(panels.Panel):
    def __init__(self, entity_manager, world_manager, context, x=0, y=0, width=None, height=None):
        super().__init__(context, x, y, width, height)

        self._entity_manager = entity_manager
        self._world_manager = world_manager

    def draw(self):
        for y in range(self._world_manager.current_map.height):
            for x in range(self._world_manager.current_map.width):
                self._put_char_ex(
                        x, y,
                        self._world_manager.current_map.tiles[x][y].glyph,
                        self._world_manager.current_map.tiles[x][y].color_lit)

        for entity, components in self._entity_manager.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            self._put_char_ex(
                    components[PositionComponent].x,
                    components[PositionComponent].y,
                    components[SpriteComponent].glyph,
                    components[SpriteComponent].color)


class MessagePanel(panels.Panel):
    def draw(self):
        pass


from roglick.components import PositionComponent,SpriteComponent,FoVComponent
from roglick.engine import panels
from roglick.lib import libtcod


# Define our panel contexts
panels.PanelContext.MapScreen = 'map'


class MapPanel(panels.Panel):
    def __init__(self, entity_manager, world_manager, context, x=0, y=0, width=None, height=None):
        super().__init__(context, x, y, width, height)

        self._entity_manager = entity_manager
        self._world_manager = world_manager

    def draw(self):
        fov = self._entity_manager.get_component(self._entity_manager.pc, FoVComponent)
        current_map = self._world_manager.current_map

        for y in range(current_map.height):
            for x in range(current_map.width):
                if libtcod.map_is_in_fov(fov.fov, x, y):
                    color = current_map.tiles[x][y].color_lit
                else:
                    color = current_map.tiles[x][y].color_unlit

                self._put_char_ex(
                        x, y,
                        current_map.tiles[x][y].glyph,
                        color)

        for entity, components in self._entity_manager.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            pos = components[PositionComponent]

            if libtcod.map_is_in_fov(fov.fov, pos.x, pos.y):
                self._put_char_ex(
                        pos.x,
                        pos.y,
                        components[SpriteComponent].glyph,
                        components[SpriteComponent].color)



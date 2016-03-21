from roglick.components import PositionComponent,SpriteComponent,FoVComponent
from roglick.engine import colors,panels
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
                tile = current_map.tiles[x][y]

                if libtcod.map_is_in_fov(fov.fov, x, y):
                    color = tile.color_lit
                    tile.explore()
                else:
                    color = tile.color_unlit

                if tile.explored:
                    self._put_char_ex(
                            x, y,
                            tile.glyph,
                            color)
                else:
                    self._put_char_ex(
                            x, y,
                            ' ',
                            colors.white, colors.black)

        for entity, components in self._entity_manager.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            pos = components[PositionComponent]

            if libtcod.map_is_in_fov(fov.fov, pos.x, pos.y):
                self._put_char_ex(
                        pos.x,
                        pos.y,
                        components[SpriteComponent].glyph,
                        components[SpriteComponent].color)



import roglick.lib.libtcodpy as libtcod


from roglick.engine.ecs.base import System
from roglick.components import PositionComponent,SpriteComponent


class RenderSystem(System):
    def set_console(self, con):
        self._con = con

    def set_map(self, the_map):
        self._map = the_map

    def execute(self):
        libtcod.console_set_default_foreground(self._con, libtcod.white)

        for y in range(self._map.height):
            for x in range(self._map.width):
                libtcod.console_put_char_ex(self._con,
                        x, y,
                        self._map.tiles[x][y].glyph.encode('UTF-8'),
                        self._map.tiles[x][y].color_lit,
                        libtcod.BKGND_NONE)
        for entity, components in self._entity_manager.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            libtcod.console_put_char_ex(self._con,
                    int(components[PositionComponent].x),
                    int(components[PositionComponent].y),
                    components[SpriteComponent].glyph.encode('UTF-8'),
                    components[SpriteComponent].color,
                    libtcod.BKGND_NONE)

        libtcod.console_blit(self._con, 0, 0, self._map.width, self._map.height, 0, 0, 0)
        libtcod.console_flush()


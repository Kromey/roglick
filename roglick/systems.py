import roglick.lib.libtcodpy as libtcod


from .ecs.base import System
from .components import PositionComponent,SpriteComponent


class RenderSystem(System):
    def set_console(self, con):
        self._con = con

    def execute(self):
        for entity, components in self._entity_manager.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            libtcod.console_put_char(self._con,
                    int(components[PositionComponent].x),
                    int(components[PositionComponent].y),
                    components[SpriteComponent].glyph.encode('UTF-8'),
                    libtcod.BKGND_NONE)


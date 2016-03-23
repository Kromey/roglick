from roglick.components import PositionComponent,SpriteComponent,FoVComponent
from roglick.engine import colors,panels,event
from roglick.lib import libtcod
from roglick.events import MessageEvent


# Define our panel contexts
panels.PanelContext.MapScreen = 'map'


class LogPanel(panels.MessagePanel):
    @event.event_handler(MessageEvent)
    def msg_event_handler(self, msgevent):
        self.add_message(msgevent.msg)


class MapPanel(panels.Panel):
    def __init__(self, entity_manager, world_manager, context, x=0, y=0, width=None, height=None):
        super().__init__(context, x, y, width, height)

        self._entities = entity_manager
        self._world = world_manager

    def draw(self):
        fov = self._entities.get_component(self._entities.pc, FoVComponent)
        current_map = self._world.current_map

        # Calculate offsets for drawing
        pcpos = self._entities.get_component(
                self._entities.pc, PositionComponent)
        ox = int(pcpos.x - self.width/2)
        oy = int(pcpos.y - self.height/2)
        # Clamp offsets so we don't draw past the edges of the map
        max_ox = current_map.width - self.width
        max_oy = current_map.height - self.height
        ox = max(0, min(max_ox, ox))
        oy = max(0, min(max_oy, oy))

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
                            x-ox, y-oy,
                            tile.glyph,
                            color)
                else:
                    self._put_char_ex(
                            x-ox, y-oy,
                            ' ',
                            colors.white, colors.black)

        for entity, components in self._entities.get_entities_with_components(
                (PositionComponent,SpriteComponent)):
            pos = components[PositionComponent]

            if libtcod.map_is_in_fov(fov.fov, pos.x, pos.y):
                self._put_char_ex(
                        pos.x-ox,
                        pos.y-oy,
                        components[SpriteComponent].glyph,
                        components[SpriteComponent].color)



from roglick.lib import libtcod
from roglick.engine import event
from roglick.engine.ecs import SystemBase
from roglick.components import PositionComponent,FoVComponent
from roglick.events import NewMapEvent,MapChangedEvent


class FoVSystem(SystemBase):
    def __init__(self):
        self._fov_algo = 0
        self._light_walls = True
        self._torch_radius = 5

    @event.event_handler(NewMapEvent,MapChangedEvent)
    def redraw_handler(self, redrawevent):
        for entity, comp in self._entity_manager.get_entities_with_component(
                FoVComponent):
            comp[FoVComponent].x = None
            comp[FoVComponent].y = None

            self._build_map(comp[FoVComponent].fov)

    def _build_map(self, fov_map):
        current_map = self._world.current_map

        width = current_map.width
        height = current_map.height

        for x in range(width):
            for y in range(height):
                libtcod.map_set_properties(
                        fov_map,
                        x,
                        y,
                        current_map.tiles[x][y].transparent,
                        current_map.tiles[x][y].passable)

    def execute(self):
        width = self._world.current_map.width
        height = self._world.current_map.height

        for entity, components in self._entity_manager.get_entities_with_components(
                (FoVComponent,PositionComponent)):
            fov = components[FoVComponent]
            pos = components[PositionComponent]

            if fov.fov is None:
                fov.x = None
                fov.y = None

                fov.fov = libtcod.map_new(width, height)
                self._build_map(fov.fov)

            if pos.x != fov.x or pos.y != fov.y:
                # Entity has moved, recompute FoV
                libtcod.map_compute_fov(
                        fov.fov,
                        pos.x,
                        pos.y,
                        self._torch_radius,
                        self._light_walls,
                        self._fov_algo)
                fov.x,fov.y = pos.x,pos.y


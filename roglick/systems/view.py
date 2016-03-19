from roglick.lib import libtcod
from roglick.engine.ecs import System
from roglick.components import PositionComponent,FoVComponent


# Temporary hack; eventually we'll need to get the actual map
MAP_WIDTH = 80
MAP_HEIGHT = 50


class FoVSystem(System):
    def __init__(self):
        self._fov_algo = 0
        self._light_walls = True
        self._torch_radius = 5

    def execute(self):
        for entity, components in self._entity_manager.get_entities_with_components(
                (FoVComponent,PositionComponent)):
            fov = components[FoVComponent]
            pos = components[PositionComponent]

            if fov.fov is None:
                fov.x = None
                fov.y = None

                fov.fov = libtcod.map_new(MAP_WIDTH, MAP_HEIGHT)
                for x in range(MAP_WIDTH):
                    for y in range(MAP_HEIGHT):
                        # TODO: Get actual map, values
                        libtcod.map_set_properties(
                                fov.fov,
                                x,
                                y,
                                True, # Transparent
                                True) # Walkable

            if pos.x != fov.x or pos.y != fov.y:
                # Entity has moved, recompute FoV
                print('Recomputing FoV...')
                libtcod.map_compute_fov(
                        fov.fov,
                        pos.x,
                        pos.y,
                        self._torch_radius,
                        self._light_walls,
                        self._fov_algo)
                fov.x,fov.y = pos.x,pos.y


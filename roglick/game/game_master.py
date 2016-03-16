from roglick.components import PositionComponent,SpriteComponent
from roglick.engine.ecs import EntityManager,SystemManager
from roglick.engine.panels import PanelManager,PanelContext
from roglick.systems import InputSystem,MovementSystem
from roglick.world import WorldManager
from roglick import panels


class GameMaster(object):
    def __init__(self):
        # We need an EntityManager of course
        self._entities = EntityManager()

        # We need a world for the game to take place in
        self._init_world()

        # Systems make everything "go"
        self._init_systems()

        # And of course we need a way to display it all
        self._init_display()

        # Last -- but certainly not least -- we'll need event handlers
        self._register_event_handlers()

        # Okay, REALLY last: We need a PC!
        self._init_pc()

    def run(self):
        self._display.draw_panels()
        self._systems.execute()

    def _init_world(self):
        self._world = WorldManager(self._entities)

    def _init_systems(self):
        self._systems = SystemManager(self._entities)

        # Populate our Systems
        self._systems.add_system(InputSystem())
        self._systems.add_system(MovementSystem())

    def _init_display(self):
        self._display = PanelManager('Ro\'glick')
        self._display.set_context(PanelContext.MapScreen)

        self._display.add_panel(
                panels.MapPanel(
                    self._entities, self._world, PanelContext.MapScreen))

    def _register_event_handlers(self):
        pass

    def _init_pc(self):
        # Get a random place to put the PC
        x,y = self._world.current_map.get_random_cell()
        pc_pos = PositionComponent(x, y)
        pc_sprite = SpriteComponent('@')

        self._entities.set_component(self._entities.pc, pc_pos)
        self._entities.set_component(self._entities.pc, pc_sprite)


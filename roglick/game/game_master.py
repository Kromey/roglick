from roglick.engine import event
from roglick.engine.ecs import EntityManager,SystemManager
from roglick.engine.panels import PanelManager,PanelContext
from roglick.events import PreInputEvent,QuitEvent,NewMapEvent
from roglick import components,systems
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

        # This flag, when True, keeps our game loop running
        self._run = True

    @event.event_handler(PreInputEvent)
    def draw_handler(self, myevent):
        self._display.draw_panels()

    @event.event_handler(QuitEvent)
    def quit_handler(self, quitevent):
        self._run = False

    @event.event_handler(NewMapEvent)
    def redraw_handler(self, redrawevent):
        self._display.clear()

    def run(self):
        while self._run:
            self._systems.execute()

    def _init_world(self):
        self._world = WorldManager(self._entities)

    def _init_systems(self):
        self._systems = SystemManager(self._entities, self._world)

        # Populate our Systems
        self._systems.add_system(systems.FatigueSystem())
        self._systems.add_system(systems.MovementSystem())
        self._systems.add_system(systems.FoVSystem())
        self._systems.add_system(systems.SkillSystem())
        self._systems.add_system(systems.InputSystem())

    def _init_display(self):
        self._display = PanelManager('Ro\'glick')
        self._display.set_context(PanelContext.MapScreen)

        self._display.add_panel(
                panels.MapPanel(
                    self._entities, self._world, PanelContext.MapScreen))
        self._display.add_panel(panels.LogPanel(PanelContext.MapScreen, y=45))

    def _register_event_handlers(self):
        # Start with ourself
        event.register(self)

        # WorldManager runs before our systems
        event.register(self._world)

        # Register system event handlers
        for system in self._systems.systems:
            event.register(system)

    def _init_pc(self):
        # Get a random place to put the PC
        x,y = self._world.current_map.get_random_cell()
        pc_pos = components.PositionComponent(x, y)
        pc_sprite = components.SpriteComponent('@')

        self._entities.set_component(self._entities.pc, pc_pos)
        self._entities.set_component(self._entities.pc, pc_sprite)
        self._entities.set_component(self._entities.pc, components.FoVComponent())
        self._entities.set_component(self._entities.pc, components.FatigueComponent())


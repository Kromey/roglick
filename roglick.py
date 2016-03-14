#!/usr/bin/env python3

from roglick.lib import libtcod
from roglick.components import PositionComponent,SpriteComponent
from roglick.systems import InputSystem,RenderSystem,MovementSystem
from roglick.engine.ecs.managers import EntityManager,SystemManager
from roglick.dungeon.maps import SimpleDungeon
from roglick.dungeon import tiles
from roglick.engine import event,panels,random
from roglick.events import MoveEvent,QuitEvent,PreInputEvent
from roglick.panels import MapPanel
from roglick.world.managers import WorldManager


SCREEN_WIDTH = 80
SCREEN_HEIGHT = 50

EM = EntityManager()
SM = SystemManager(EM)

pc_pos = PositionComponent(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
pc_sprite = SpriteComponent('@')

EM.set_component(EM.pc, pc_pos)
EM.set_component(EM.pc, pc_sprite)

WM = WorldManager(EM)
dungeon = WM.current_map

msg_panel = panels.MessagePanel(panels.PanelContext.MapScreen, 0, SCREEN_HEIGHT-5, height=5)
# And another; this is getting messy, really need to get a proper game init/loop....
def move_message(moveevent):
    global msg_panel
    msg_panel.add_message(str(moveevent))
    return event.PASS
event.register(move_message, MoveEvent)

PM = panels.PanelManager('Ro\'glick')
PM.add_panel(MapPanel(EM, WM, panels.PanelContext.MapScreen))
PM.add_panel(msg_panel)
PM.set_context(panels.PanelContext.MapScreen)

# Start the PC in a random walkable space
while not dungeon.tiles[pc_pos.x][pc_pos.y].is_passable:
    pc_pos.x = random.get_int(0, dungeon.width-1)
    pc_pos.y = random.get_int(0, dungeon.height-1)

SM.create_system(InputSystem)
SM.create_system(MovementSystem)

# Dirty hack, but works for now
quit = False
def quit_handler(quitevent):
    global quit
    quit = True
    return event.PASS
event.register(quit_handler, QuitEvent)

# Another temporary/dirty hack
def draw_handler(inputevent):
    global PM
    PM.draw_panels()
    return event.PASS
event.register(draw_handler, PreInputEvent)

while not libtcod.console_is_window_closed() and not quit:
    SM.execute()


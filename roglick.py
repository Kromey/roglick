#!/usr/bin/env python3

from roglick.lib import libtcod
from roglick.components import PositionComponent,SpriteComponent
from roglick.systems import InputSystem,RenderSystem,MovementSystem
from roglick.engine.ecs.managers import EntityManager,SystemManager
from roglick.dungeon.maps import SimpleDungeon
from roglick.dungeon import tiles
from roglick.engine import event,panels
from roglick.events import QuitEvent
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

PM = panels.PanelManager('Ro\'glick')
PM.add_panel(MapPanel(EM, WM, panels.PanelContext.MapScreen))
PM.set_context(panels.PanelContext.MapScreen)

start_room = dungeon.rooms[libtcod.random_get_int(0, 0, len(dungeon.rooms)-1)]
pc_pos.x = int((start_room.x1 + start_room.x2)/2)
pc_pos.y = int((start_room.y1 + start_room.y2)/2)

SM.create_system(InputSystem)
SM.create_system(MovementSystem)

# Dirty hack, but works for now
quit = False
def quit_handler(quitevent):
    global quit
    quit = True
    return event.PASS
event.register(quit_handler, QuitEvent)

while not libtcod.console_is_window_closed() and not quit:
    PM.draw_panels()
    SM.execute()


#!/usr/bin/env python3

import roglick.lib.libtcodpy as libtcod
from roglick.components import PositionComponent,SpriteComponent
from roglick.systems import InputSystem,RenderSystem
from roglick.ecs.managers import EntityManager,SystemManager
from roglick.dungeon.base import Map
from roglick.dungeon import tiles


SCREEN_WIDTH = 80
SCREEN_HEIGHT = 50

EM = EntityManager()
SM = SystemManager(EM)

pc_pos = PositionComponent(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
pc_sprite = SpriteComponent('@')

EM.set_component(EM.pc, pc_pos)
EM.set_component(EM.pc, pc_sprite)

libtcod.console_set_custom_font(b'data/fonts/arial10x10.png', libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(SCREEN_WIDTH, SCREEN_HEIGHT, b'python/libtcod tutorial', False)

con = libtcod.console_new(SCREEN_WIDTH, SCREEN_HEIGHT)

dungeon = Map(SCREEN_WIDTH, SCREEN_HEIGHT, fill=tiles.FloorTile)

render_sys = RenderSystem()
render_sys.set_console(con)
render_sys.set_map(dungeon)
SM.add_system(render_sys)

input_sys = InputSystem()
SM.add_system(input_sys)

while not libtcod.console_is_window_closed():
    SM.execute()


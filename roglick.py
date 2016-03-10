#!/usr/bin/env python3

import roglick.lib.libtcodpy as libtcod
from roglick.components import PositionComponent,SpriteComponent
from roglick.systems import InputSystem,RenderSystem
from roglick.ecs.managers import EntityManager,SystemManager
from roglick.dungeon.maps import SimpleDungeon
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

#dungeon = Map(SCREEN_WIDTH, SCREEN_HEIGHT, fill=tiles.FloorTile)
dungeon = SimpleDungeon(SCREEN_WIDTH, SCREEN_HEIGHT)

render_sys = RenderSystem()
render_sys.set_console(con)
render_sys.set_map(dungeon)
SM.add_system(render_sys)

start_room = dungeon.rooms[libtcod.random_get_int(0, 0, len(dungeon.rooms)-1)]
pc_pos.x = int((start_room.x1 + start_room.x2)/2)
pc_pos.y = int((start_room.y1 + start_room.y2)/2)

SM.create_system(InputSystem)

while not libtcod.console_is_window_closed():
    SM.execute()


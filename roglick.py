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

PC = EM.create_entity()

pc_pos = PositionComponent(SCREEN_WIDTH/2, SCREEN_HEIGHT/2)
pc_sprite = SpriteComponent('@')

EM.set_component(PC, pc_pos)
EM.set_component(PC, pc_sprite)

libtcod.console_set_custom_font(b'data/fonts/arial10x10.png', libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_TCOD)
libtcod.console_init_root(SCREEN_WIDTH, SCREEN_HEIGHT, b'python/libtcod tutorial', False)

con = libtcod.console_new(SCREEN_WIDTH, SCREEN_HEIGHT)

dungeon = Map(SCREEN_WIDTH, SCREEN_HEIGHT, fill=tiles.FloorTile)

render_sys = RenderSystem()
render_sys.set_console(con)
render_sys.set_map(dungeon)
SM.add_system(render_sys)

input_sys = InputSystem()
input_sys.set_pc(PC)
SM.add_system(input_sys)

def handle_keys():
    global EM, PC

    key = libtcod.console_wait_for_keypress(True)
    if key.vk == libtcod.KEY_ENTER and key.lalt:
        #Alt+Enter: toggle fullscreen
        libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

    elif key.vk == libtcod.KEY_ESCAPE:
        return True  #exit game

    pos = EM.get_component(PC, PositionComponent)

    #movement keys
    if libtcod.console_is_key_pressed(libtcod.KEY_UP):
        pos.y -= 1

    elif libtcod.console_is_key_pressed(libtcod.KEY_DOWN):
        pos.y += 1

    elif libtcod.console_is_key_pressed(libtcod.KEY_LEFT):
        pos.x -= 1

    elif libtcod.console_is_key_pressed(libtcod.KEY_RIGHT):
        pos.x += 1

    EM.set_component(PC, pos)


while not libtcod.console_is_window_closed():
    SM.execute()

    #handle keys and exit game if needed
    #exit = handle_keys()
    #if exit:
    #    break


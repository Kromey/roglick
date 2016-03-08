import roglick.lib.libtcodpy as libtcod
from roglick.ecs.base import System
from roglick.components import PositionComponent


class InputSystem(System):
    def execute(self):
        key = libtcod.console_wait_for_keypress(True)
        if key.vk == libtcod.KEY_ENTER and key.lalt:
            #Alt+Enter: toggle fullscreen
            libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

        elif key.vk == libtcod.KEY_ESCAPE:
            return True  #exit game

        pos = self._entity_manager.get_component(self._entity_manager.pc, PositionComponent)

        #movement keys
        if libtcod.console_is_key_pressed(libtcod.KEY_UP):
            pos.y -= 1

        elif libtcod.console_is_key_pressed(libtcod.KEY_DOWN):
            pos.y += 1

        elif libtcod.console_is_key_pressed(libtcod.KEY_LEFT):
            pos.x -= 1

        elif libtcod.console_is_key_pressed(libtcod.KEY_RIGHT):
            pos.x += 1

        self._entity_manager.set_component(self._entity_manager.pc, pos)

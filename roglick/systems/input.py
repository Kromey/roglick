import roglick.lib.libtcodpy as libtcod
from roglick.engine.ecs import System
from roglick.components import PositionComponent
from roglick.events import MoveEvent
from roglick.engine import event


class InputSystem(System):
    def execute(self):
        key = libtcod.console_wait_for_keypress(True)
        if key.vk == libtcod.KEY_ENTER and key.lalt:
            #Alt+Enter: toggle fullscreen
            libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

        elif key.vk == libtcod.KEY_ESCAPE:
            return True  #exit game

        pc = self._entity_manager.pc

        #movement keys
        if libtcod.console_is_key_pressed(libtcod.KEY_UP):
            event.dispatch(MoveEvent(pc, 0, -1))

        elif libtcod.console_is_key_pressed(libtcod.KEY_DOWN):
            event.dispatch(MoveEvent(pc, 0, 1))

        elif libtcod.console_is_key_pressed(libtcod.KEY_LEFT):
            event.dispatch(MoveEvent(pc, -1, 0))

        elif libtcod.console_is_key_pressed(libtcod.KEY_RIGHT):
            event.dispatch(MoveEvent(pc, 1, 0))


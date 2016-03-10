import roglick.lib.libtcodpy as libtcod
from roglick.engine.ecs import System
from roglick.components import PositionComponent
from roglick.events import MoveEvent
from roglick.engine import event


class InputSystem(System):
    def execute(self):
        key = self.get_keypress()
        if key.vk == libtcod.KEY_ENTER and key.lalt:
            #Alt+Enter: toggle fullscreen
            libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

        elif key.vk == libtcod.KEY_ESCAPE:
            return True  #exit game

        pc = self._entity_manager.pc

        # Movement keys
        # Orthoganal movement
        if key.vk == libtcod.KEY_KP8:
            event.dispatch(MoveEvent(pc, 0, -1))
        elif key.vk == libtcod.KEY_KP2:
            event.dispatch(MoveEvent(pc, 0, 1))
        elif key.vk == libtcod.KEY_KP4:
            event.dispatch(MoveEvent(pc, -1, 0))
        elif key.vk == libtcod.KEY_KP6:
            event.dispatch(MoveEvent(pc, 1, 0))
        # Diagonal movement
        elif key.vk == libtcod.KEY_KP7:
            event.dispatch(MoveEvent(pc, -1, -1))
        elif key.vk == libtcod.KEY_KP9:
            event.dispatch(MoveEvent(pc, 1, -1))
        elif key.vk == libtcod.KEY_KP1:
            event.dispatch(MoveEvent(pc, -1, 1))
        elif key.vk == libtcod.KEY_KP3:
            event.dispatch(MoveEvent(pc, 1, 1))

    def get_keypress(self):
        key = libtcod.console_wait_for_keypress(True)

        if not key.pressed:
            return self.get_keypress()

        # Translate key.c into its character reprsentation
        if key.vk == libtcod.KEY_CHAR:
            key.c = chr(key.c)
        return key


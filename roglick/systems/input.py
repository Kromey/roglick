import roglick.lib.libtcodpy as libtcod
from roglick.engine.ecs import System
from roglick.components import PositionComponent
from roglick.events import MoveEvent
from roglick.engine import event


class InputSystem(System):
    def execute(self):
        key = self.get_keypress()
        if key == libtcod.KEY_ENTER and key:
            #Alt+Enter: toggle fullscreen
            libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

        elif key == libtcod.KEY_ESCAPE:
            return True  #exit game

        pc = self._entity_manager.pc

        # Movement keys
        # Orthoganal movement
        if key == libtcod.KEY_KP8:
            event.dispatch(MoveEvent(pc, 0, -1))
        elif key == libtcod.KEY_KP2:
            event.dispatch(MoveEvent(pc, 0, 1))
        elif key == libtcod.KEY_KP4:
            event.dispatch(MoveEvent(pc, -1, 0))
        elif key == libtcod.KEY_KP6:
            event.dispatch(MoveEvent(pc, 1, 0))
        # Diagonal movement
        elif key == libtcod.KEY_KP7:
            event.dispatch(MoveEvent(pc, -1, -1))
        elif key == libtcod.KEY_KP9:
            event.dispatch(MoveEvent(pc, 1, -1))
        elif key == libtcod.KEY_KP1:
            event.dispatch(MoveEvent(pc, -1, 1))
        elif key == libtcod.KEY_KP3:
            event.dispatch(MoveEvent(pc, 1, 1))

    def get_keypress(self):
        """Wrapper method for retrieving keypress events from th keyboard

        A bug(?) in libtcod means that the wait_for_keypress function actually
        returns key press AND release events, resulting in each tap of a key
        functioning as two "keypress" events. To work around this, we wait for
        a key and then test if it is actually in the 'pressed' state and, if
        not, wait again.

        This wrapper also checks for printable keys and translates key.c into
        the corresponding character.
        """
        key = libtcod.console_wait_for_keypress(True)

        if not key.pressed and key.vk != libtcod.KEY_NONE:
            return self.get_keypress()

        # Translate key.c into its character reprsentation
        if key.vk == libtcod.KEY_CHAR:
            return chr(key.c)
        return key.vk


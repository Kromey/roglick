from roglick.lib import libtcod
from roglick.engine.ecs import System
from roglick.components import PositionComponent
from roglick.events import MoveEvent,QuitEvent
from roglick.engine import event


class InputSystem(System):
    # Define movement keys with corresponding (dx,dy) tuples
    MOVEMENT_KEYS = {
            libtcod.KEY_KP1: (-1,1),
            libtcod.KEY_KP2: (0,1),
            libtcod.KEY_KP3: (1,1),
            libtcod.KEY_KP4: (-1,0),
            libtcod.KEY_KP6: (1,0),
            libtcod.KEY_KP7: (-1,-1),
            libtcod.KEY_KP8: (0, -1),
            libtcod.KEY_KP9: (1,-1),
            'y': (-1,-1),
            'u': (1,-1),
            'h': (-1,0),
            'j': (0,1),
            'k': (0,-1),
            'l': (1,0),
            'b': (-1,1),
            'n': (1,1),
            }

    def execute(self):
        """Wait for player input, dispatching appropriate events."""
        key = self.get_keypress()
        if key == libtcod.KEY_ENTER and key:
            #Alt+Enter: toggle fullscreen
            libtcod.console_set_fullscreen(not libtcod.console_is_fullscreen())

        elif key == libtcod.KEY_ESCAPE:
            event.dispatch(QuitEvent())  #exit game

        pc = self._entity_manager.pc

        # Movement keys
        if key in self.MOVEMENT_KEYS:
            event.dispatch(MoveEvent(pc, *self.MOVEMENT_KEYS[key]))

    def get_keypress(self):
        """Wrapper method for retrieving keypress events from the keyboard

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


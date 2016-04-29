import time


from roglick.lib import libtcod
from roglick.engine.ecs import SystemBase
from roglick.components import FatigueComponent,PositionComponent
from roglick.events import ClimbDownEvent,ClimbUpEvent,MoveEvent,QuitEvent,PreInputEvent
from roglick.engine import event


class InputSystem(SystemBase):
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
        pc = self._entity_manager.pc

        pc_fatigue = self._entity_manager.get_component(pc, FatigueComponent)
        if pc_fatigue.fatigue > 0:
            # PC's still fatigued, need to wait until they can act
            return

        event.dispatch(PreInputEvent())

        key = self.get_keypress()

        if key == libtcod.KEY_ESCAPE or libtcod.console_is_window_closed():
            event.dispatch(QuitEvent())  #exit game

        # Movement keys
        if key in self.MOVEMENT_KEYS:
            event.dispatch(MoveEvent(pc, *self.MOVEMENT_KEYS[key]))
        elif key == '>':
            event.dispatch(ClimbDownEvent(pc))
        elif key == '<':
            event.dispatch(ClimbUpEvent(pc))

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
        while True:
            key = libtcod.console_wait_for_keypress(True)

            #if not key.pressed and key.vk != libtcod.KEY_NONE:
            #    # Make sure we actually get a pressed key
            #    return self.get_keypress()
            if key.vk == libtcod.KEY_SHIFT or key.vk == libtcod.KEY_CONTROL:
                # We don't care about these keys, just ignore them
                continue

            if key.pressed:
                if key.vk == libtcod.KEY_F12:
                    # Take a screenshot, pause briefly, then resume waiting
                    libtcod.sys_save_screenshot()
                    time.sleep(0.5)
                elif key.vk == libtcod.KEY_CHAR:
                    # Translate key.c into its character reprsentation
                    return chr(key.c)
                else:
                    # Return the key code
                    return key.vk
            elif key.vk == libtcod.KEY_NONE:
                # Ensure non-key events (e.g. closing the window) can propagate
                return None


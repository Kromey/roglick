from roglick.lib import libtcod
from roglick.engine import colors


SCREEN_WIDTH = 80
SCREEN_HEIGHT = 50


class PanelContext(object):
    """PanelContext is used to "switch" between sets of visible Panels.

    Client code should define a set of contexts as class attributes on this
    class.
    """
    pass


class PanelManager(object):
    """An object to simplify working with multiple logical panels with libtcod

    A new root console is created with the parameters supplied. You can then
    add sub-classed Panel objects to the PanelManager. When the draw_panels()
    method is called, only Panel objects matching the current (or supplied)
    context will be drawn; the others will be ignored, effectively rendering
    them invisible.
    """
    def __init__(self, title, width=SCREEN_WIDTH, height=SCREEN_HEIGHT, font='data/fonts/terminal12x12_gs_ro.png'):
        self._panels = []
        self._context = None
        self._width = width
        self._height = height

        libtcod.console_set_custom_font(font.encode('UTF-8'), libtcod.FONT_TYPE_GREYSCALE | libtcod.FONT_LAYOUT_ASCII_INROW)
        libtcod.console_init_root(width, height, title.encode('UTF-8'), False)

        self._con = libtcod.console_new(width, height)

    def add_panel(self, panel):
        """Add a panel to this object."""
        panel.con = self._con

        # Calculate x/y offsets if necessary
        if panel.x < 0:
            panel.x = self._width + panel.x
        if panel.y < 0:
            panel.y = self._height + panel.y
        # Calculate width/height offsets if necessary
        if panel.width is not None and panel.width < 0:
            panel.width = self._width + panel.width - panel.x
        if panel.height is not None and panel.height < 0:
            panel.height = self._height + panel.height - panel.y

        self._panels.append(panel)

    def clear(self):
        libtcod.console_clear(self._con)

    @property
    def panels(self):
        return self._panels

    @property
    def context(self):
        """Retrieve the current panel context.

        Only Panels matching the current (or supplied) context will be drawn.
        """
        return self._context

    def set_context(self, context):
        """Set the current panel context."""
        self._context = context

    def draw_panels(self, context=None):
        """Draw all panels matching the current context.

        If the context parameter is supplied, draw those panels instead; using
        this parameter does NOT change the manager's current context.
        """
        if context is None:
            context = self._context

        for panel in self._panels:
            # Only draw panels for the current context
            if panel.context == context:
                # Calculate and auto-width or -height dimensions before drawing
                if panel.width is None:
                    panel.width = self._calculate_panel_dimension('x', panel.x, panel.context, self._width)
                if panel.height is None:
                    panel.height = self._calculate_panel_dimension('y', panel.y, panel.context, self._height)

                panel.draw()

        libtcod.console_blit(self._con, 0, 0, self._width, self._height, 0, 0, 0)
        libtcod.console_flush()

    def _calculate_panel_dimension(self, dimension, start_coord, panel_context, max_dimension):
        boundary = max_dimension
        for panel in self._panels:
            if panel.context == panel_context:
                dim = getattr(panel, dimension)
                if dim > start_coord:
                    boundary = min(boundary, dim)

        return boundary - start_coord


class Panel(object):
    """This class provides a base class for Panel objects.

    This class must be sub-classed to provide the necessary logic for drawing
    whatever it is responsible for. This class does provide methods for sub-
    classes to easily draw to the Panel's correct portion of the console.
    """
    def __init__(self, context, x=0, y=0, width=None, height=None):
        """Create a Panel at the x,y coordinates with the given width,height.

        If width or height are None, the Panel is automatically sized to fill
        the screen.
        """
        self._context = context

        self.x = x
        self.y = y
        self.width = width
        self.height = height

        self.con = None

    def draw(self):
        """Draw this Panel.

        Panel MUST be sub-classed and this method implemented with the proper
        logic for drawing whatever the Panel is responsible for.
        """
        raise NotImplementedError("Panel must be subclassed, and the draw method defined")

    @property
    def context(self):
        return self._context

    def _put_char_ex(self, x, y, char, color=colors.white, bgcolor=colors.black):
        """Draw the specified character at the x,y coordinates on this Panel.

        This method automatically handles ensuring that the supplied character
        is being drawn at valid coordinates, as well as maps them to the proper
        place on the console.
        """
        if self.con is None:
            # Do nothing if we don't have a console
            return

        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            # Ignore out-of-bounds characters; simplifies client code
            return

        # We draw as if we're at 0,0, but this panel may be elsewhere on the console
        x = x + self.x
        y = y + self.y

        libtcod.console_put_char_ex(self.con,
                int(x), int(y),
                char.encode('UTF-8'), color, bgcolor)

    def _put_string(self, x, y, string):
        """Draw the string at the given x,y coordinates.
        """
        if self.con is None:
            # Do nothing if we don't have a console
            return

        if x < 0 or x >= self.width or y < 0 or y >= self.height:
            # Ignore out-of-bounds characters; simplifies client code
            return

        x = x + self.x
        y = y + self.y

        libtcod.console_print(self.con, x, y, string.encode('UTF-8'))


class MessagePanel(Panel):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)

        self._messages = []

    def add_message(self, msg):
        self._messages.append(msg)

        # No reason to clutter memory with messages we can't display
        while len(self._messages) > self.height:
            self._messages.pop(0)

    def draw(self):
        for y in range(len(self._messages)):
            # Right-pad the message with spaces to the panel's full width
            self._put_string(0, y, '{msg: <{fill}}'.format(
                msg=self._messages[y], fill=self.width))

